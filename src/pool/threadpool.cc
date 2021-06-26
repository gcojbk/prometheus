#include "threadpool.h"

ThreadPool::ThreadPool(uint32_t n) {
    InitPool(n);
}

ThreadPool::~ThreadPool() {
    Stop();
}

void ThreadPool::InitPool(uint32_t n) {
    uint32_t hard_max = std::thread::hardware_concurrency();
    max_threads_ = n > hard_max ? hard_max : n;
    for (uint32_t i = 0; i < max_threads_; i++) {
        workers_.emplace_back(
            [this] {
                while (true) {
                    std::function<void()> job;
                    {
                        std::unique_lock<std::mutex> lock(job_mtx_);
                        cond_.wait(lock, [this] { return this->is_stop_ || !job_queue_.empty(); });
                        if (this->is_stop_ && job_queue_.empty()) {
                            return;
                        }
                        if (job_queue_.empty()) {
                            continue;
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
    std::unique_lock<std::mutex> lock(job_mtx_);
    is_stop_.store(true);
    cond_.notify_all();
    for (auto& t : workers_) {
        t.join();
    }
}

// end of file threadpool.cc
