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

    std::ifstream in("data.txt", std::ios::in);
    if (in.is_open())
    {
        std::string data;
        std::getline(in, data);

        char delimiter = ',';
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(data);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        glm::vec3 position, front, up;
        position.x = std::stof(tokens[0]);
        position.y = std::stof(tokens[1]);
        position.z = std::stof(tokens[2]);
        front.x = std::stof(tokens[3]);
        front.y = std::stof(tokens[4]);
        front.z = std::stof(tokens[5]);
        up.x = std::stof(tokens[6]);
        up.y = std::stof(tokens[7]);
        up.z = std::stof(tokens[8]);
        mainCamera->cameraPos = position;
        mainCamera->cameraFront = front;
        mainCamera->cameraUp = up;
        // firstMouse = false;
        // lastX = std::stof(tokens[9]);
        // lastY = std::stof(tokens[10]);
        yaw = (double)std::stof(tokens[11]);
        pitch = (double)std::stof(tokens[12]);
    }

    Cube *box = new Cube("container2.png", "container2_specular.png");
    Cube *light = new Cube(nullptr, nullptr);
    glm::vec3 lightPos = glm::vec3(4.0f, 4.0f, 4.0f);
    Shader *vertexShader = new Shader(AssetsLoader("light.vs").getPath());
    Shader *fragmentShader = new Shader(AssetsLoader("light.fs").getPath());
    Program *program = new Program(vertexShader, fragmentShader);
    light->setProgram(program);
    light->setScale(0.2f);
    light->setLocation(lightPos);

    // ----------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        calcFPS(window);
        mainCamera->processInput();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        box->program->setUniform("material.diffuse", 0);
        box->program->setUniform("material.specular", 1);
        box->program->setUniform("material.shininess", 64.0f);

        box->program->setUniform("light.position", lightPos);
        box->program->setUniform("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        box->program->setUniform("light.diffuse", glm::vec3(0.2f, 0.2f, 0.2f));
        box->program->setUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        light->render(mainCamera);
        box->program->setUniform("viewPos", mainCamera->cameraPos);
        box->render(mainCamera);

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
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        std::ofstream out("data.txt");
        glm::vec3 pos = (mainCamera->cameraPos);
        glm::vec3 front = (mainCamera->cameraFront);
        glm::vec3 up = (mainCamera->cameraUp);
        // fprintf(stdout, "%f,%f,%f\n", pos.x, pos.y, pos.z);
        out << pos.x << "," << pos.y << "," << pos.z << ","
            << front.x << "," << front.y << "," << front.z << ","
            << up.x << "," << up.y << "," << up.z << ","
            << lastX << "," << lastY << "," << yaw << "," << pitch;
        out.close();
    }
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