#include "header.h"

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void calcFPS(GLFWwindow *window);

int scrWidth = 800;
int scrHeight = 600;

bool canMove = false;

int frameNum = 0;
double lastTime = 0;

Camera *mainCamera;
Cube *cube1;
Cube *cube2;

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();
    glfwSwapInterval(1);

    // ----------------------------------------------------------------------

    glm::vec3 position = glm::vec3(0.0f, 0.0f, -30.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    mainCamera = new Camera(window, position, target);
    cube1 = new Cube("wall.jpg");
    // cube2 = new Cube("container.jpg");

    cube1->setLocation(glm::vec3(10.0f, 10.0f, 10.0f));
    // cube1->setScale(glm::vec3(1.2f, 0.4f, 0.6f));
    // cube1->setRotation(glm::vec3(0.0f, -10.0f, 0.0f));
    // cube2->setRotation(glm::vec3(20.0f, 45.0f, 360.0f));

    // ----------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        calcFPS(window);

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube1->render(mainCamera);
        // cube2->render(mainCamera);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    canMove = (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_REPEAT);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveForward(1.0f);
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveForward(-1.0f);
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveRight(1.0f);
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveRight(-1.0f);
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveUp(1.0f);
    if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cube1->moveUp(-1.0f);
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