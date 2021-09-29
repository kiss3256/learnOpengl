#include "header.h"

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
static void calcFPS(GLFWwindow *window);

int scrWidth = 800;
int scrHeight = 600;

int frameNum = 0;
double lastTime = 0;

Camera *mainCamera;

double lastX = 400, lastY = 300;
bool firstMouse = true;
double yaw = 0, pitch = 0;

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();
    glfwSwapInterval(1);

    // ----------------------------------------------------------------------

    mainCamera = new Camera(window);
    Cube *box = new Cube("wall.jpg");
    Cube *light = new Cube;

    Shader *vertexShader = new Shader(AssetsLoader("light.vs").getPath());
    Shader *fragmentShader = new Shader(AssetsLoader("light.fs").getPath());
    Program *program = new Program(vertexShader, fragmentShader);
    glm::vec3 lightPos = glm::vec3(4.0f, 4.0f, 4.0f);
    program->setUniform("lightPos", lightPos);
    light->setProgram(program);
    light->setScale(0.2f);
    light->setLocation(lightPos);

    // ----------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        calcFPS(window);

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainCamera->processInput();

        box->render(mainCamera);
        light->render(mainCamera);
        // cube2->render(mainCamera);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = (float)(xpos - lastX);
    float yoffset = (float)(lastY - ypos);
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = (float)sin(glm::radians(yaw));
    front.y = (float)sin(glm::radians(pitch));
    front.z = -(float)cos(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
    mainCamera->cameraFront = glm::normalize(front);
    // fprintf(stdout, "front::(%f, %f, %f)\n", front.x, front.y, front.z);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
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