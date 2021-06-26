#include <gtest/gtest.h>
#include "threadpool.h"

auto tpTask = [](int& s, int a)->void { s += a; };

void t1(int& s, int a) {
    s += a;
}

TEST(test_threadpool, test_threadpool) {
    int res = 0;
    int expect = 0;
    int thread_counts = 1;
    ThreadPool threadpool(thread_counts);
    for (int i = 0; i < 3; i++) {
        threadpool.AddWork(tpTask, res, i);
        expect += i;
    }
    threadpool.Stop();

    EXPECT_EQ(res, expect);
}