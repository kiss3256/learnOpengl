#include "Shader.hpp"


using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}


Shader::Shader(const char* filename, GLenum type) {
    std::string w_filename = filename;
    #ifdef  WIN32
    w_filename = "../" + w_filename;
    #endif  //WIN32  
    
    string file_contents;
    file_contents = readFileIntoString(w_filename);

    const char* shaderSource = file_contents.c_str();
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
