#include "header.h"
#include <thread>
#include <sys/stat.h>

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void calcFPS(GLFWwindow *window);
void drawGround();
void loadCameraStatus();

int scrWidth = 800;
int scrHeight = 600;

int frameNum = 0;
double lastTime = 0;

Camera *mainCamera;

double lastX = 400, lastY = 300;
bool firstMouse = true;
double yaw = 0, pitch = 0;

bool rightButtonDown = false;

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
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    loadCameraStatus();

    Ground ground;
    Model monkey(AssetsLoader("monkey-head.obj").getPath().c_str());
    Program *program = new Program("model.vs", "model.fs");
    bool reload = false;

    auto thread_function = [&]
    {
        long double lastModification = 0;
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));

            struct stat buf;
            stat(AssetsLoader("model.fs").getPath().c_str(), &buf);
            long double modification = buf.st_mtime;

            if (lastModification != modification)
            {
                std::cout << "time of last data modification::" << std::to_string(modification) << std::endl;
                lastModification = modification;

                reload = true;
            }
        }
    };

    std::thread t(thread_function);
    t.detach();

    // ----------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        calcFPS(window);
        mainCamera->processInput();

        if (reload)
        {
            reload = false;

            glfwMakeContextCurrent(window);
            delete program;
            program = new Program("model.vs", "model.fs");
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ground.draw(mainCamera);

        program->setUniform("model", glm::value_ptr(glm::mat4(1)));
        program->setUniform("view", glm::value_ptr(mainCamera->getViewMatrix()));
        program->setUniform("projection", glm::value_ptr(mainCamera->getProjectionMatrix()));
        monkey.Draw(*program);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (!rightButtonDown)
        return;
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

    if (yaw > 360.0f)
        yaw -= 360.0f;
    if (yaw < -360.0f)
        yaw += 360.0f;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = (float)sin(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
    front.y = (float)sin(glm::radians(pitch));
    front.z = -(float)cos(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
    mainCamera->cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    float sensitivity = 0.05f;
    glm::vec4 pos(mainCamera->cameraPos, 0.0f);
    glm::vec4 front(mainCamera->cameraFront, 0.0f);
    glm::mat4 mat(1.0f);
    float yawRadians = (float)xoffset * sensitivity;
    float pitchRadians = (float)yoffset * sensitivity;
    mat = glm::rotate(mat, yawRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    mainCamera->cameraPos = pos * mat;
    mainCamera->cameraFront = glm::normalize(front * mat);
    yaw += glm::degrees(yawRadians);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    rightButtonDown = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
    firstMouse = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
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

void loadCameraStatus()
{
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