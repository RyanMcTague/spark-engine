#ifndef SPARK_ENGINE_RENDERER_H
#define SPARK_ENGINE_RENDERER_H
#include "spark/core/base.h"
#include "spark/renderer/shader.h"
#include "spark/renderer/mesh.h"
#include "spark/renderer/texture_2d.h"

namespace Spark{
    SPARK_API class Renderer{
    private:
        Shader* m_spriteShader;
        Shader* m_spriteSheetShader;
        GLRef   m_spriteVAO;
        GLRef   m_spriteVBO;
        GLRef   m_spriteEBO;
        float    m_scale;
        mat4    m_projection{};
        mat4    m_model{};
        vec3    m_cameraPos{};

        void UpdateCamera();
        void BuildSpriteMesh();
    public:
        Renderer();
        ~Renderer();
        void SetScale(float scale);
        void SetPosition(const vec2& position);
        void DrawSprite(const vec2& position, const vec2& scale,
                        const vec2& size, const vec2& tile, const float& rotation, Texture2D* texture);
    };
}

#endif //SPARK_ENGINE_RENDERER_H
