#include "Ground.hpp"

Ground::Ground()
{
    float vertices[] = {
        -5.0f, -5.0f, 5.0f, -5.0f,
        -5.0f, -4.0f, 5.0f, -4.0f,
        -5.0f, -3.0f, 5.0f, -3.0f,
        -5.0f, -2.0f, 5.0f, -2.0f,
        -5.0f, -1.0f, 5.0f, -1.0f,
        -5.0f, 0.0f, 5.0f, 0.0f,
        -5.0f, 1.0f, 5.0f, 1.0f,
        -5.0f, 2.0f, 5.0f, 2.0f,
        -5.0f, 3.0f, 5.0f, 3.0f,
        -5.0f, 4.0f, 5.0f, 4.0f,
        -5.0f, 5.0f, 5.0f, 5.0f,

        -5.0f, 5.0f, -5.0f, -5.0f,
        -4.0f, 5.0f, -4.0f, -5.0f,
        -3.0f, 5.0f, -3.0f, -5.0f,
        -2.0f, 5.0f, -2.0f, -5.0f,
        -1.0f, 5.0f, -1.0f, -5.0f,
        0.0f, 5.0f, 0.0f, -5.0f,
        1.0f, 5.0f, 1.0f, -5.0f,
        2.0f, 5.0f, 2.0f, -5.0f,
        3.0f, 5.0f, 3.0f, -5.0f,
        4.0f, 5.0f, 4.0f, -5.0f,
        5.0f, 5.0f, 5.0f, -5.0f};

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    const char *groundVertexShader = "#version 410 core\n"
                                     "\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = projection * view * model * vec4(aPos.x, 0.0f, aPos.y, 1.0f);\n"
                                     "}\0";
    const char *groundFragmentShader = "#version 410 core\n"
                                       "\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                                       "}\0";
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &groundVertexShader, nullptr);
    glCompileShader(vertex);

    {
        GLint success;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILE::" << infoLog << std::endl;
        }
    }

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &groundFragmentShader, nullptr);
    glCompileShader(fragment);

    {
        GLint success;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILE::" << infoLog << std::endl;
        }
    }

    groundProgram = glCreateProgram();
    glAttachShader(groundProgram, vertex);
    glAttachShader(groundProgram, fragment);
    glLinkProgram(groundProgram);
    {
        GLint success;
        glGetProgramiv(groundProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetProgramInfoLog(groundProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::LINK_PROGRAM::" << infoLog << std::endl;
        }
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Ground::~Ground()
{
}

void Ground::draw(Camera *mainCamera)
{
    glUseProgram(groundProgram);
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    GLuint loc_model = glGetUniformLocation(groundProgram, "model");
    glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(model));
    GLuint loc_view = glGetUniformLocation(groundProgram, "view");
    glUniformMatrix4fv(loc_view, 1, GL_FALSE, glm::value_ptr(mainCamera->getViewMatrix()));
    GLuint loc_projection = glGetUniformLocation(groundProgram, "projection");
    glUniformMatrix4fv(loc_projection, 1, GL_FALSE, glm::value_ptr(mainCamera->getProjectionMatrix()));

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 88);
    glBindVertexArray(0);
}