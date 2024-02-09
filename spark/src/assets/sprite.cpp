#include "spark/assets/sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Spark::Sprite::Sprite(const std::string& path) {
    auto fs = cmrc::spark::get_filesystem();
    m_isSpriteSheet = false;
    auto file = fs.open(path);
    int width, height, nrChannels;
    uint8_t* data = stbi_load_from_memory((uint8_t*)&file.begin()[0], file.size(), &width, &height, &nrChannels, 0);
    if (data){
        m_texture = new Texture2D();
        m_texture->SetFilter(TextureFilter::Nearest, TextureFilter::Nearest);
        m_texture->Load(width, height, data);
        m_tileSize = {width, height};
    }
    else{
        Logger::Error("Failed to load texture");
    }
    stbi_image_free(data);
}

Spark::Sprite::Sprite(const std::string& path, const vec2& tileSize){
    auto fs = cmrc::spark::get_filesystem();
    m_isSpriteSheet = true;
    m_tileSize = tileSize;
    auto file = fs.open(path);
    int width, height, nrChannels;
    uint8_t* data = stbi_load_from_memory((uint8_t*)&file.begin()[0], file.size(), &width, &height, &nrChannels, 0);
    if (data){
        m_texture = new Texture2D();
        m_texture->SetFilter(TextureFilter::Nearest, TextureFilter::Nearest);
        m_texture->Load(width, height, data);
    }
    else{
        Logger::Error("Failed to load texture");
    }
    stbi_image_free(data);
}

Spark::Sprite::~Sprite(){
    delete m_texture;
};

Spark::Texture2D* Spark::Sprite::GetTexture(){
    return m_texture;
}

const Spark::vec2& Spark::Sprite::GetTileSize(){
    return m_tileSize;
}

bool Spark::Sprite::IsSpiteSheet(){
    return m_isSpriteSheet;
}