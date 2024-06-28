#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#pragma once
class Logger {
public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> guard(mutex_);
        std::cout << message << std::endl;
        logfile_ << message << std::endl;
    }

private:
    Logger() : logfile_("logs/log.txt", std::ios_base::out | std::ios_base::app) {}
    ~Logger() { logfile_.close(); }

    std::ofstream logfile_;
    std::mutex mutex_;
};
#define Log(message) \
    Logger::getInstance().log(message)
#define Console(message) \
    std::cout << message << std::endl;
#endif 