#include "log.h"
#include <gtest/gtest.h>


TEST(test_log, test_log) {
    logger::info("aaaaa{}, {}\n", 123, "asdasd");
    logger::error("this is test {}\n", "ERROR");
    logger::setLogMode(logger::LogMode::FILE);
    logger::setLogFile("log");
    logger::info("test log to file!\n");
}