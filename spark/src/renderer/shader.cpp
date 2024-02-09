#include "spark/renderer/shader.h"

Spark::UUID Spark::Shader::m_nextID = 0;

std::string Spark::Shader::GetShaderExt(uint32_t type){
    switch (type) {
        case GL_VERTEX_SHADER:
            return ".vert";
        case GL_FRAGMENT_SHADER:
            return ".frag";
        default:
            return "";
    }
}

Spark::ShaderType Spark::Shader::GetShaderTypeFromExt(const std::string& ext){
    Spark::ShaderType type;
    if (ext.find(".glsl.vert") != std::string::npos)
        type = Spark::ShaderType::Vertex;
    else if (ext.find(".glsl.frag") != std::string::npos)
        type = Spark::ShaderType::Fragment;
    else
        type = Spark::ShaderType::NoType;
    return type;
}



Spark::Shader::Shader(const std::string &name) {
    m_id = GlNullRef;
    if (name.empty()){
        m_name = "untitled_" + std::to_string(m_nextID++);
    } else{
        m_name = name;
    }
}


Spark::Shader::~Shader() {
    if(m_id != GlNullRef){
        glDeleteProgram(m_id);
    }
}

Spark::Shader Spark::Shader::FromFile(const std::string& path){
    auto fs = cmrc::spark::get_filesystem();
    auto endIdx = path.find_last_of('/');
    std::string shaderBaseName = path;

    if (endIdx != std::string::npos){
        shaderBaseName = path.substr(endIdx + 1);
    }

    auto startIdx = path.find_last_not_of(shaderBaseName);
    std::string shaderBaseDir = path.substr(0, startIdx);
    Shader shader(path);

    for(const auto& obj: fs.iterate_directory(shaderBaseDir)){
        if (obj.is_directory() || obj.filename().find(shaderBaseName) == std::string::npos)
            continue;
        ShaderType type = GetShaderTypeFromExt(obj.filename());
        auto file = fs.open(shaderBaseDir + "/" + shaderBaseName + GetShaderExt(type));
        shader.AddShaderSource(type, &file.begin()[0]);
    }

    shader.Compile();
    return shader;
}

void Spark::Shader::AddShaderSource(ShaderType type, const char* source){
    auto it = m_source.find(type);
    if (it == m_source.end()){
        m_source.emplace(type, source);
    } else{
        m_source[type] = source;
    }
}

bool Spark::Shader::Compile() {
    std::map<ShaderType, GLRef> shaders;
    int success;
    int infoLogLength;
    char* infoLog;
    bool hasError = false;

    if (m_id != GlNullRef){
        Logger::Warn(m_name + " is already compiled!");
        return false;
    }

    m_id = glCreateProgram();

    for(auto& el : m_source){
        ShaderType type = el.first;
        const char* source = el.second;

        GLRef shader = glCreateShader((uint32_t)type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        if(success == GL_FALSE){
            infoLog = new char[infoLogLength];
            glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);

            Logger::Error("Could not compile " + m_name + GetShaderExt(type));
            Logger::Print(infoLog);
            delete infoLog;
            hasError = true;
        } else{
            glAttachShader(m_id, shader);
        }
        shaders.emplace(type, shader);
    }

    if (!hasError){
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (success == GL_FALSE){
            infoLog = new char[infoLogLength];
            glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog);
            glDeleteProgram(m_id);
            m_id = GlNullRef;

            Logger::Error("Could not link " + m_name);
            Logger::Print(infoLog);
            delete infoLog;

        }
    } else{
        Logger::Error("Could not link " + m_name);
        glDeleteProgram(m_id);
        m_id = GlNullRef;
    }

    for(auto& el: shaders){
        glDeleteShader(el.second);
    }
    if (m_id == GlNullRef){
        assert(false);
    }
    return m_id != GlNullRef;
}



void Spark::Shader::Bind() {
    if (m_id != GlNullRef){
        glUseProgram(m_id);
    } else{
        Logger::Warn("Shader \"" + m_name + "\" is not valid!");
    }
}

void Spark::Shader::UniformVec3(const std::string& name, const vec3& vec) const{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Spark::Shader::UniformVec2(const std::string& name, const vec2& vec){
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform2f(location, vec.x, vec.y);
}

void Spark::Shader::UniformMat4(const std::string& name, const mat4& mat){
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}