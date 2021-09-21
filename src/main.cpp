#include "header.h"

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void calcFPS(GLFWwindow *window);

int scrWidth = 800;
int scrHeight = 600;

int frameNum = 0;
double lastTime = 0;

const std::string winTitle("LearnOpenGL");

int main(int, char **)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(scrWidth, scrHeight, winTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();
    glfwSwapInterval(1);

    // ----------------------------------------------------------------------

    Shader *vertexShader = new Shader(AssetsLoader("cube.vs").getPath());
    Shader *fragmentShader = new Shader(AssetsLoader("cube.fs").getPath());
    Program *program = new Program(vertexShader, fragmentShader);
    Cube *cube = new Cube("wall.jpg");

    // ----------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        calcFPS(window);

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);

        program->setUniform("model", glm::value_ptr(model));
        program->setUniform("view", glm::value_ptr(view));
        program->setUniform("projection", glm::value_ptr(projection));
        // program->setUniform("ourTexture", 0);

        cube->render();

        program->use();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    scrWidth = width;
    scrHeight = height;
    glViewport(0, 0, width, height);
}

void calcFPS(GLFWwindow *window)
{
    if (frameNum == 60)
    {
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        std::string fps = std::to_string(frameNum / elapsedTime);
        std::string newTitle = winTitle + "( FPS = " + fps + " )";
        glfwSetWindowTitle(window, newTitle.c_str());

        frameNum = 0;
    }

    frameNum++;
}