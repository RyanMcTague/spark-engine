#ifndef SPARK_ENGINE_FILE_DIALOG_H
#define SPARK_ENGINE_FILE_DIALOG_H
#include "spark_editor/base.h"

namespace FileDialog{
    enum class Status{
        Okay,
        Canceled,
        Error,
        None,
    };

    struct Result{
        Status status = Status::None;
        std::string path;
    };

    Result OpenImage();

    Result SaveTileMap();

    Result CreateProject();
    Result OpenProject();
}


#endif //SPARK_ENGINE_FILE_DIALOG_H
