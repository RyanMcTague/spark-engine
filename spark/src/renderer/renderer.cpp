#include "spark/renderer/renderer.h"


const char* VERTEX_SPRITE_SHADER =R"(
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
uniform mat4 uMVP;
out vec2 TexCoord;
void main(){
    TexCoord = aUV;
    gl_Position = uMVP * vec4(aPosition, 1.0);
}
)";

const char* FRAGMENT_SPRITE_SHADER = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main(){
   FragColor = texture(ourTexture, TexCoord);
}
)";



const char* VERTEX_SPRITESHEET_SHADER =R"(
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
uniform mat4 uMVP;
out vec2 inTexCoord;
void main(){
    inTexCoord = aUV;
    gl_Position = uMVP * vec4(aPosition, 1.0);
}
)";

const char* FRAGMENT_SPRITESHEET_SHADER = R"(
#version 330 core
out vec4 FragColor;
in vec2 inTexCoord;
uniform sampler2D ourTexture;
uniform vec2 uTileSize;
uniform vec2 uTileBottomLeft;
uniform vec2 uTextureSize;

void main(){
    vec2 TexCoord;
    TexCoord.x = inTexCoord.x * (uTileSize.x/uTextureSize.x) + (uTileBottomLeft.x/uTextureSize.x);
    TexCoord.y = inTexCoord.y * (uTileSize.y/uTextureSize.y) + (uTileBottomLeft.y/uTextureSize.y);
    FragColor = texture(ourTexture, TexCoord);
}
)";


float square[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,  // top left
};

uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
};

Spark::Renderer::Renderer() {
    m_spriteEBO = GlNullRef;
    m_spriteVBO = GlNullRef;
    m_spriteVAO = GlNullRef;
    m_scale = 1.0;
    m_cameraPos = vec3(0.0f, 0.0f, -1.0f);

    m_spriteShader = new Shader("spark::shaders:sprite");
    m_spriteShader->AddShaderSource(ShaderType::Vertex, VERTEX_SPRITE_SHADER);
    m_spriteShader->AddShaderSource(ShaderType::Fragment, FRAGMENT_SPRITE_SHADER);
    m_spriteShader->Compile();

    m_spriteSheetShader = new Shader("spark::shaders:spritesheet");
    m_spriteSheetShader->AddShaderSource(ShaderType::Vertex, VERTEX_SPRITESHEET_SHADER);
    m_spriteSheetShader->AddShaderSource(ShaderType::Fragment, FRAGMENT_SPRITESHEET_SHADER);
    m_spriteSheetShader->Compile();

    BuildSpriteMesh();
    UpdateCamera();
}

void Spark::Renderer::BuildSpriteMesh(){
    glGenVertexArrays(1, &m_spriteVAO);
    glGenBuffers(1, &m_spriteVBO);
    glGenBuffers(1, &m_spriteEBO);

    glBindVertexArray(m_spriteVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_spriteVBO);
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), square, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float ), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float ), (void*)(3 * sizeof(float )));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Spark::Renderer::~Renderer() {
    if(m_spriteEBO != GlNullRef){
        glDeleteBuffers(1, &m_spriteEBO);
    }

    if(m_spriteVBO != GlNullRef){
        glDeleteBuffers(1, &m_spriteVBO);
    }

    if(m_spriteVAO != GlNullRef){
        glDeleteVertexArrays(1, &m_spriteVAO);
    }
    delete m_spriteShader;
    delete m_spriteSheetShader;
}

void Spark::Renderer::UpdateCamera(){
    auto* window = glfwGetCurrentContext();
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    m_projection = glm::ortho(
             m_cameraPos.x * m_scale,
             (float)width * m_scale + m_cameraPos.x * m_scale,
             (float)height * m_scale + m_cameraPos.y * m_scale,
             m_cameraPos.y * m_scale,
             -1.0f, 1.0f);
}
void Spark::Renderer::SetScale(float scale){
    m_scale = 1 / scale;
    UpdateCamera();
}
void Spark::Renderer::SetPosition(const vec2& position){
    m_cameraPos = vec3(position.x, position.y, -1.0f);
    UpdateCamera();
}


void Spark::Renderer::DrawSprite(const vec2& position, const vec2& scale,
                const vec2& size, const vec2& tile, const float& rotation, Texture2D* texture){
    vec2 bl = vec2(size.x * tile.x, size.y * tile.y);
    m_model = mat4(1.0f);
    m_model = glm::translate(m_model, vec3(position.x + size.x * scale.x * 0.5f,
                                           position.y + size.y * scale.y * 0.5f,
                                           0.0f));
    m_model = glm::rotate(m_model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, glm::vec3(size.x * scale.x, size.y * scale.y, 1.0f));
    m_spriteSheetShader->Bind();
    texture->Bind();
    m_spriteSheetShader->UniformMat4("uMVP", m_projection * m_model);
    m_spriteSheetShader->UniformVec2("uTileSize", size);
    m_spriteSheetShader->UniformVec2("uTileBottomLeft", bl);
    m_spriteSheetShader->UniformVec2("uTextureSize", texture->GetSize());

    glCheck(glBindVertexArray(m_spriteVAO));
    glCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    glCheck(glBindVertexArray(0));
}
