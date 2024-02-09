#include "spark_editor/utility/file_system.h"

std::string FileSystem::GetFileNameFromPath(const std::string& path){
    size_t idx = path.find_last_of('/');
    if (idx == std::string::npos)
        idx = 0;
    return path.substr(idx + 1, (path.find_last_of('.')));
}

std::string FileSystem::GetBaseDirFromPath(const std::string& path){
    size_t idx = path.find_last_of('/');
    if (idx == std::string::npos)
        idx = 0;
    return path.substr(0, idx);
}
