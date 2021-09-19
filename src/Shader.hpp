#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader {
    public:
    Shader(const char* filename, GLenum type);
    ~Shader();

    GLuint shader;

};