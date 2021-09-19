#include "Shader.hpp"


Shader::Shader(const char* filename, GLenum type) {
    std::vector<char> v;
    if (FILE *fp = fopen(filename, "r")) {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            v.insert(v.end(), buf, buf + len);
        v.push_back('\0');
        fclose(fp);
    }

    const char* shaderSource = v.data();
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(shader);
}
