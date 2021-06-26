#ifndef UTIL_THREADPOOL_H_
#define UTIL_THREADPOOL_H_

#include <condition_variable>
#include <mutex>
#include <atomic>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <future>

class ThreadPool {
 public:
    ThreadPool(uint32_t n);
    ~ThreadPool();

    template <typename Func, typename... Args >
    void AddWork(Func&& f, Args&&... args);

    void Stop();

 private:
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    void InitPool(uint32_t n);

 private:
    std::mutex                          job_mtx_;
    std::condition_variable             cond_;
    std::vector<std::thread>            workers_;
    std::queue<std::function<void()>>   job_queue_;
    std::atomic<bool>                   is_stop_;
    uint32_t                            max_threads_;
};


template <typename Func, typename... Args >
void ThreadPool::AddWork(Func&& f, Args&&... args) {
    using return_type = typename std::result_of<Func(Args...)>::type;
    using task_type = std::packaged_task<return_type()>;
    auto task = std::make_shared< std::packaged_task<return_type()> >
                (std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
    auto retVal = task->get_future();
    {
        std::unique_lock<std::mutex> lock(job_mtx_);
        job_queue_.emplace([task](){ (*task)(); });
        cond_.notify_one();
    }
    return;
}

#endif // end of UTIL_THREADPOOL_H_