#include "spark/assets/tilemap.h"
#include <iostream>
Spark::Tilemap::Tilemap(const std::string& path){
    auto fs = cmrc::spark::get_filesystem();
    auto file = fs.open(path);
    tilesX = 0;
    tilesY = 0;
    Parse(&file.begin()[0]);
}
Spark::Tilemap::~Tilemap() = default;

void Spark::Tilemap::Parse(const std::string& source) {
    std::stringstream ss;
    ss << source;
    std::string line;
    int nextLayer = 0;
    while (std::getline(ss, line)){
        if (line.find("@layer") != std::string::npos){
            nextLayer++;
            layers.emplace_back();
            continue;
        }
        auto width = line.find("@tilesX = ");
        auto end = line.find('\n');
        if (width != std::string::npos){
            tilesX = std::stoi(line.substr(line.find_first_not_of("@tilesX = "), end));
            continue;
        }

        auto height = line.find("@tilesY = ");
        if (height != std::string::npos){
            tilesY = std::stoi(line.substr(line.find_first_not_of("@tilesY = "), end));
            continue;
        }

        int layer = nextLayer - 1;
        std::string pos;
        std::stringstream ss2;
        ss2 << line;
        while (std::getline(ss2, pos, ' ')){
            int x, y;
            auto idx = pos.find('#');
            if (idx != std::string::npos){
                x = std::stoi(pos.substr(0, idx));
                y = std::stoi(pos.substr(idx + 1));
                layers[layer].emplace_back(x, y);
            }
        }
    }
}