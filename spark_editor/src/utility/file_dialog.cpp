#include "spark_editor/utility/file_dialog.h"

FileDialog::Result FileDialog::OpenImage(){
    nfdchar_t *outPath;
    std::string path;
    nfdfilteritem_t filterItem[1] = { { "Image", "png,jpg,jpeg" }};
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, nullptr);
    Result res;
    if (result == NFD_OKAY)
    {
        res.path.assign(outPath);
        NFD_FreePath(outPath);
        res.status = Status::Okay;

    }
    else if (result == NFD_ERROR){
        spdlog::error(NFD_GetError());
        res.status = Status::Error;
    }
    else{
        res.status = Status::Canceled;
    }
    return res;
}
FileDialog::Result FileDialog::SaveTileMap(){
    nfdchar_t *outPath;
    std::string path;
    nfdfilteritem_t filterItem[1] = {{ "Tilemap", "tm" }};
    nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, nullptr, nullptr);
    Result res;
    if (result == NFD_OKAY)
    {
        res.path.assign(outPath);
        NFD_FreePath(outPath);
        res.status = Status::Okay;

    }
    else if (result == NFD_ERROR){
        spdlog::error(NFD_GetError());
        res.status = Status::Error;
    }
    else{
        res.status = Status::Canceled;
    }
    return res;
}

FileDialog::Result FileDialog::CreateProject(){
    nfdchar_t *outPath;
    std::string path;
    nfdfilteritem_t filterItem[1] = {{ "Project", "sp" }};
    nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, nullptr, nullptr);
    Result res;
    if (result == NFD_OKAY)
    {
        res.path.assign(outPath);
        NFD_FreePath(outPath);
        res.status = Status::Okay;

    }
    else if (result == NFD_ERROR){
        spdlog::error(NFD_GetError());
        res.status = Status::Error;
    }
    else{
        res.status = Status::Canceled;
    }
    return res;
}

FileDialog::Result FileDialog::OpenProject(){
    nfdchar_t *outPath;
    std::string path;
    nfdfilteritem_t filterItem[1] = {{ "Project", "sp" }};
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, nullptr);
    Result res;
    if (result == NFD_OKAY)
    {
        res.path.assign(outPath);
        NFD_FreePath(outPath);
        res.status = Status::Okay;

    }
    else if (result == NFD_ERROR){
        spdlog::error(NFD_GetError());
        res.status = Status::Error;
    }
    else{
        res.status = Status::Canceled;
    }
    return res;
}