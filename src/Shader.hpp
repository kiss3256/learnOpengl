#include <glad/glad.h>
#include <iostream>
#include <vector>

class Shader {
    public:
    Shader(const char* filename, GLenum type);
    ~Shader();

    GLuint shader;

};