#ifndef SPARK_ENGINE_SHADER_H
#define SPARK_ENGINE_SHADER_H
#include "spark/core/base.h"
#include "spark/renderer/opengl.h"

namespace Spark{
    SPARK_API enum ShaderType {
        Vertex      = GL_VERTEX_SHADER,
        Fragment    = GL_FRAGMENT_SHADER,
        NoType      = GL_NONE
    };

    SPARK_API class Shader{
    private:
        static UUID m_nextID;

        std::string m_name;
        GLRef m_id;
        std::map<ShaderType, const char*> m_source;

        static std::string GetShaderExt(uint32_t type);
        static ShaderType GetShaderTypeFromExt(const std::string& ext);

    public:
        explicit Shader(const std::string &name = "");
        ~Shader();

        static Shader FromFile(const std::string& path);

        void AddShaderSource(ShaderType type, const char* source);
        bool Compile();
        void Bind();
        void UniformVec2(const std::string& name, const vec2& vec);
        void UniformVec3(const std::string& name, const vec3& vec) const;
        void UniformMat4(const std::string& name, const mat4& mat);
    };
}

#endif //SPARK_ENGINE_SHADER_H
