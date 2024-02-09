#ifndef SPARK_ENGINE_LOGGER_H
#define SPARK_ENGINE_LOGGER_H
#include <string>
#include "spark/core/platform.h"
namespace Spark{
    SPARK_API struct Logger{
        static void Initialize();
        static void Error(const std::string& msg);
        static void Warn(const std::string& msg);
        static void Info(const std::string& msg);
        static void Debug(const std::string& msg);
        static void Print(const std::string& msg);
    };
}

#endif //SPARK_ENGINE_LOGGER_H
