#ifndef UTIL_THREADPOOL_H_
#define UTIL_THREADPOOL_H_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
  ThreadPool(uint32_t n);
  ~ThreadPool();

  template <typename Func, typename... Args>
  auto AddWork(Func &&func, Args &&... args)
      -> std::future<typename std::result_of<Func(Args...)>::type>;

  void Stop();

private:
  ThreadPool(const ThreadPool &) = delete;
  ThreadPool &operator=(const ThreadPool &) = delete;
  void InitPool(uint32_t n);

private:
  std::mutex job_mtx_;
  std::condition_variable cond_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> job_queue_;
  std::atomic<bool> is_stop_;
  uint32_t max_threads_;
};

ThreadPool::ThreadPool(uint32_t n) : is_stop_(false) { InitPool(n); }

ThreadPool::~ThreadPool() {
  if (is_stop_.load() == false) {
    Stop();
  }
}

template <typename Func, typename... Args>
auto ThreadPool::AddWork(Func &&func, Args &&... args)
    -> std::future<typename std::result_of<Func(Args...)>::type> {
  using return_type = typename std::result_of<Func(Args...)>::type;
  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
  auto retVal = task->get_future();
  {
    std::unique_lock<std::mutex> lock(job_mtx_);
    job_queue_.emplace([task]() { (*task.get())(); });
  }
  cond_.notify_one();
  return retVal;
}

void ThreadPool::InitPool(uint32_t n) {
  max_threads_ = n;
  for (uint32_t i = 0; i < max_threads_; i++) {
    workers_.emplace_back([this] {
      while (true) {
        std::function<void()> job;
        {
          std::unique_lock<std::mutex> lock(this->job_mtx_);
          this->cond_.wait(lock, [this] {
            return this->is_stop_.load() || !job_queue_.empty();
          });
          if (this->is_stop_.load() && job_queue_.empty()) {
            return;
          }
          job = std::move(job_queue_.front());
          job_queue_.pop();
        }
        job();
      }
    });
  }
}

void ThreadPool::Stop() {
  {
    std::unique_lock<std::mutex> lock(job_mtx_);
    is_stop_.store(true);
  }
  cond_.notify_all();
  for (auto &t : workers_) {
    t.join();
  }
}

#endif // end of UTIL_THREADPOOL_H_
