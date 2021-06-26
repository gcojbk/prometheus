#include <gtest/gtest.h>
#include "threadpool.hpp"

auto tpTask = [](int& s, int a)->int { s += a; return a; };

int g_sum = 0;

TEST(test_threadpool, test_threadpool) {
    int expect = 0;
    int thread_counts = 4;
    ThreadPool threadpool(thread_counts);
    for (int i = 0; i < 1000; i++) {
        std::future<int> ret = threadpool.AddWork(tpTask, std::ref<int>(g_sum), i);  // bind need std::ref to judge if a reference 
        EXPECT_EQ(ret.get(), i);
        expect += i;
    }
    threadpool.Stop();

    EXPECT_EQ(g_sum, expect);
}