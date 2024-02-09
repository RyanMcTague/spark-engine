#ifndef SPARK_ENGINE_FILE_SYSTEM_H
#define SPARK_ENGINE_FILE_SYSTEM_H
#include "spark_editor/base.h"

namespace FileSystem{
    std::string GetFileNameFromPath(const std::string& path);
    std::string GetBaseDirFromPath(const std::string& path);
}
#endif //SPARK_ENGINE_FILE_SYSTEM_H
