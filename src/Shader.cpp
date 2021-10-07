#include "Shader.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostringstream;
using std::size_t;
using std::string;

string readFileIntoString(const string &path)
{
    ifstream input_file(path);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

Shader::Shader(string filename)
{
    string file_contents;
    file_contents = readFileIntoString(filename);
    const char *shaderSource = file_contents.c_str();

    size_t found;
    found = filename.find(".vs");
    if (found != string::npos)
        type = GL_VERTEX_SHADER;

    found = filename.find(".fs");
    if (found != string::npos)
        type = GL_FRAGMENT_SHADER;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_COMPILE::" << infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteShader(shader);
    std::cout << "LOG::" << type << "::Shader deleted.\n";
}
