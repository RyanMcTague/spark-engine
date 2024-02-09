#include "spark/utility/logger.h"
#include "spdlog/spdlog.h"
#include <iostream>
void Spark::Logger::Initialize() {
    spdlog::set_level(spdlog::level::debug);
}

void Spark::Logger::Error(const std::string &msg) {
    spdlog::error(msg);
}

void Spark::Logger::Warn(const std::string &msg) {
    spdlog::warn(msg);
}

void Spark::Logger::Info(const std::string &msg) {
    spdlog::info(msg);
}

void Spark::Logger::Debug(const std::string &msg) {
    spdlog::debug(msg);
}
void Spark::Logger::Print(const std::string &msg) {
    std::cout << msg << std::endl;
}

