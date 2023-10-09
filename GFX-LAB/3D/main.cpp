#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float Fan_rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
bool fanIsOn = false;

float test_rotaionY = 0.0;

// camera

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
//BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cube_vertices[] = {
        -0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f,
        0.25f, -0.25f, -0.25f, 1.0f, 1.0f, 1.0f,
        0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f,
        -0.25f, 0.25f, -0.25f, 1.0f, 1.0f, 1.0f,
        -0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f,
        0.25f, -0.25f, 0.25f, 1.0f, 1.0f, 1.0f,
        0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f,
        -0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f,
    };
    float cube_verticesBlade[] = {
        -0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
        0.25f, -0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
        0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
        -0.25f, 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
        -0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
        0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
        0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
        -0.25f, 0.25f, 0.25f, 0.0f, 1.0f, 0.0f,
    };

    float cube_verticesCenter[] = {
        -0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
        0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
        0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
        -0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 0.0f,
        -0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
        0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
        0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
        -0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f,
    };

    float cube_verticesGreen[] = {
        -0.25f, -0.25f, -0.25f, 0.0156f, 0.18f, 0.035f,
        0.25f, -0.25f, -0.25f, 0.0156f, 0.18f, 0.035f,
        0.25f, 0.25f, -0.25f, 0.0156f, 0.18f, 0.035f,
        -0.25f, 0.25f, -0.25f, 0.0156f, 0.18f, 0.035f,
        -0.25f, -0.25f, 0.25f, 0.0156f, 0.18f, 0.035f,
        0.25f, -0.25f, 0.25f, 0.0156f, 0.18f, 0.035f,
        0.25f, 0.25f, 0.25f, 0.0156f, 0.18f, 0.035f,
        -0.25f, 0.25f, 0.25f, 0.0156f, 0.18f, 0.035f,
    };
    float cube_verticesSky[] = {
        -0.25f, -0.25f, -0.25f, 0.7f, 0.3, 0.939,
        0.25f, -0.25f, -0.25f, 0.7f, 0.3, 0.939,
        0.25f, 0.25f, -0.25f, 0.7f, 0.3, 0.939,
        -0.25f, 0.25f, -0.25f, 0.7f, 0.3, 0.939,
        -0.25f, -0.25f, 0.25f, 0.7f, 0.3, 0.939,
        0.25f, -0.25f, 0.25f, 0.7f, 0.3, 0.939,
        0.25f, 0.25f, 0.25f, 0.7f, 0.3, 0.939,
        -0.25f, 0.25f, 0.25f, 0.7f, 0.3, 0.939,
    };

    float cube_vertices3[] = {
        -0.25f, -0.25f, -0.25f,0.411 , 0.17 , 0.129,
        0.25f, -0.25f, -0.25f, 0.411 , 0.17 , 0.129,
        0.25f, 0.25f, -0.25f, 0.411 , 0.17 , 0.129,
        -0.25f, 0.25f, -0.25f, 0.411 , 0.17 , 0.129,
        -0.25f, -0.25f, 0.25f, 0.411 , 0.17 , 0.129,
        0.25f, -0.25f, 0.25f, 0.411 , 0.17 , 0.129,
        0.25f, 0.25f, 0.25f, 0.411 , 0.17 , 0.129,
        -0.25f, 0.25f, 0.25f, 0.411 , 0.17 , 0.129
    };

    float cube_vertices2[] = {
     -0.25f, -0.25f, -0.25f, 0.552, 0.224, 0.224,
     0.25f, -0.25f, -0.25f, 0.552, 0.224, 0.224,
     0.25f, 0.25f, -0.25f, 0.552, 0.224, 0.224,
     -0.25f, 0.25f, -0.25f, 0.552, 0.224, 0.224,
     -0.25f, -0.25f, 0.25f, 0.552, 0.224, 0.224,
     0.25f, -0.25f, 0.25f, 0.552, 0.224, 0.224,
     0.25f, 0.25f, 0.25f, 0.552, 0.224, 0.224,
     -0.25f, 0.25f, 0.25f, 0.552, 0.224, 0.224,
    };

    float cube_vertices4[] = {
        -0.25f, -0.25f, -0.25f, 0.18,0.015,0.071,
        0.25f, -0.25f, -0.25f, 0.18,0.015,0.071,
        0.25f, 0.25f, -0.25f, 0.18,0.015,0.071,
        -0.25f, 0.25f, -0.25f, 0.18,0.015,0.071,
        -0.25f, -0.25f, 0.25f, 0.18,0.015,0.071,
        0.25f, -0.25f, 0.25f, 0.18,0.015,0.071,
        0.25f, 0.25f, 0.25f, 0.18,0.015,0.071,
        -0.25f, 0.25f, 0.25f, 0.18,0.015,0.071
    };

    float circle_vertices5[] = {
        0.0,.70,0.0, 0.0,0.0,0.0,
       0.25,.70,0.0, 0.0,1.0,1.0,
       .177,.70,0.177, 0.0,1.0,1.0,
       0.0,.70,0.25, 0.0,1.0,1.0,
       -.177,.70,0.177, 0.0,1.0,1.0,
       -0.25,.70,0.0, 0.0,1.0,1.0,
       -.177,.70,-0.177, 0.0,1.0,1.0,
       0.0,.70,-0.25, 0.0,1.0,1.0,
       .177,.70,-0.177, 0.0,1.0,1.0,


       0.0,-.30,0.0, 0.0,0.0,0.0,
       1.0 / 2,-.30,0.0, 0.0,1.0,1.0,
       .707 / 2,-.30,.707 / 2, 0.0,1.0,1.0,
       0.0,-.30,1.0 / 2, 0.0,1.0,1.0,
       -.707 / 2,-.30,.707 / 2, 0.0,1.0,1.0,
       -1.0 / 2,-.30,0.0, 0.0,1.0,1.0,
       -.707 / 2,-.30,-.707 / 2, 0.0,1.0,1.0,
       0.0,-.30,-1.0 / 2, 0.0,1.0,1.0,
       .707 / 2,-.30,-.707 / 2, 0.0,1.0,1.0,
       
    };

    float cube_verticesBlack[] = {
        -0.25f, -0.25f, -0.25f,0.0 , 0.0 , 0.0,
        0.25f, -0.25f, -0.25f, 0.0 , 0.0 , 0.0,
        0.25f, 0.25f, -0.25f, 0.0 , 0.0 , 0.0,
        -0.25f, 0.25f, -0.25f, 0.0 , 0.0 , 0.0,
        -0.25f, -0.25f, 0.25f, 0.0 , 0.0 , 0.0,
        0.25f, -0.25f, 0.25f, 0.0 , 0.0 , 0.0,
        0.25f, 0.25f, 0.25f, 0.0 , 0.0 , 0.0,
        -0.25f, 0.25f, 0.25f, 0.0 , 0.0 , 0.0
    };

    float cube_verticesYello[] = {
        -0.25f, -0.25f, -0.25f,.909 , 0.804 , 0.262,
        0.25f, -0.25f, -0.25f, .909 , 0.804 , 0.262,
        0.25f, 0.25f, -0.25f, .909 , 0.804 , 0.262,
        -0.25f, 0.25f, -0.25f, .909 , 0.804 , 0.262,
        -0.25f, -0.25f, 0.25f, .909 , 0.804 , 0.262,
        0.25f, -0.25f, 0.25f, .909 , 0.804 , 0.262,
        0.25f, 0.25f, 0.25f, .909 , 0.804 , 0.262,
        -0.25f, 0.25f, 0.25f, .909 , 0.804 , 0.262
    };

    float cube_verticesOrange[] = {
        -0.25f, -0.25f, -0.25f,.86 , 0.156 , 0.035,
        0.25f, -0.25f, -0.25f, .86 , 0.156 , 0.035,
        0.25f, 0.25f, -0.25f, .86 , 0.156 , 0.035,
        -0.25f, 0.25f, -0.25f, .86 , 0.156 , 0.035,
        -0.25f, -0.25f, 0.25f, .86 , 0.156 , 0.035,
        0.25f, -0.25f, 0.25f, .86 , 0.156 , 0.035,
        0.25f, 0.25f, 0.25f, .86 , 0.156 , 0.035,
        -0.25f, 0.25f, 0.25f, .86 , 0.156 , 0.035
    };

    float cube_verticesWall[] = {
        -0.25f, -0.25f, -0.25f,0.87 , 0.87 , .80,
        0.25f, -0.25f, -0.25f, 0.87 , 0.87 , .80,
        0.25f, 0.25f, -0.25f, 0.87 , 0.87 , .80,
        -0.25f, 0.25f, -0.25f, 0.87 , 0.87 , .80,
        -0.25f, -0.25f, 0.25f, 0.87 , 0.87 , .80,
        0.25f, -0.25f, 0.25f, 0.87 , 0.87 , .80,
        0.25f, 0.25f, 0.25f, 0.87 , 0.87 , .80,
        -0.25f, 0.25f, 0.25f, 0.87 , 0.87 , .80
    };

    float cube_verticesFloor[] = {
        -0.25f, -0.25f, -0.25f,0.027 , 0.184 , .51,
        0.25f, -0.25f, -0.25f, 0.027 , 0.184 , .51,
        0.25f, 0.25f, -0.25f, 0.027 , 0.184 , .51,
        -0.25f, 0.25f, -0.25f, 0.027 , 0.184 , .51,
        -0.25f, -0.25f, 0.25f, 0.027 , 0.184 , .51,
        0.25f, -0.25f, 0.25f, 0.027 , 0.184 , .51,
        0.25f, 0.25f, 0.25f, 0.027 , 0.184 , .51,
        -0.25f, 0.25f, 0.25f, 0.027 , 0.184 , .51
    };

    float cube_verticesTop[] = {
        -0.25f, -0.25f, -0.25f,0.87 , 0.6 , 0.94,
        0.25f, -0.25f, -0.25f, 0.87 , 0.6 , 0.94,
        0.25f, 0.25f, -0.25f, 0.87 , 0.6 , 0.94,
        -0.25f, 0.25f, -0.25f, 0.87 , 0.6 , 0.94,
        -0.25f, -0.25f, 0.25f, 0.87 , 0.6 , 0.94,
        0.25f, -0.25f, 0.25f, 0.87 , 0.6 , 0.94,
        0.25f, 0.25f, 0.25f, 0.87 , 0.6 , 0.94,
        -0.25f, 0.25f, 0.25f, 0.87 , 0.6 , 0.94
    };

    float cube_verticesBack[] = {
        -0.25f, -0.25f, -0.25f,0.54 , 0.733 , 0.90,
        0.25f, -0.25f, -0.25f, 0.54 , 0.733 , 0.90,
        0.25f, 0.25f, -0.25f, 0.54 , 0.733 , 0.90,
        -0.25f, 0.25f, -0.25f, 0.54 , 0.733 , 0.90,
        -0.25f, -0.25f, 0.25f, 0.54 , 0.733 , 0.90,
        0.25f, -0.25f, 0.25f, 0.54 , 0.733 , 0.90,
        0.25f, 0.25f, 0.25f, 0.54 , 0.733 , 0.90,
        -0.25f, 0.25f, 0.25f, 0.54 , 0.733 , 0.90
    };
    
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        1, 2, 6,
        6, 5, 1,

        5, 6, 7,
        7 ,4, 5,

        4, 7, 3,
        3, 0, 4,

        6, 2, 3,
        3, 7, 6,

        1, 5, 4,
        4, 0, 1
    };


    unsigned int circle_indices[] = {
       0,1,2,
       0,2,3,
       0,3,4,
       0,4,5,
       0,5,6,
       0,6,7,
       0,7,8,
       0,8,1,

       9,10,11,
       9,11,12,
       9,12,13,
       9,13,14,
       9,14,15,
       9,15,16,
       9,16,17,
       9,17,10,
       
       1,10,2,
       10,11,2,
       11,2,12,
       2,12,3,
       3,12,13,
       3,13,4,
       4,13,14,
       4,14,5,
       5,14,15,
       5,15,6,
       6,15,16,
       6,16,7,
       7,16,17,
       7,17,8,
       8,17,10,
       8,10,1,


    };


    //axis line 

    float axisVertices[] = {
        // X-axis
        0.0f, 0.0f, 0.0f,   // Start point
        5.0f, 0.0f, 0.0f,   // End point

        // Y-axis
        0.0f, 0.0f, 0.0f,   // Start point
        0.0f, 5.0f, 0.0f,   // End point

        // Z-axis
        0.0f, 0.0f, 0.0f,   // Start point
        0.0f, 0.0f, 5.0f    // End point
    };
    

    //axis line VBO,VAO
    unsigned int axisVAO, axisVBO;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);

    // Bind the axis VAO and VBO
    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //test Cube
    unsigned int testVBO, testVAO, testEBO;
    glGenVertexArrays(1, &testVAO);
    glGenBuffers(1, &testVBO);
    glGenBuffers(1, &testEBO);

    glBindVertexArray(testVAO);

    glBindBuffer(GL_ARRAY_BUFFER, testVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices2), cube_vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //actual
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);



    //circle_test

    unsigned int circle_VBO, circle_VAO, circle_EBO;
    glGenVertexArrays(1, &circle_VAO);
    glGenBuffers(1, &circle_VBO);
    glGenBuffers(1, &circle_EBO);

    glBindVertexArray(circle_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, circle_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices5), circle_vertices5, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circle_indices), circle_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);



    //ourShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix,fan_scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        
        //floor

        
     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, testVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesFloor), cube_verticesFloor, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

     float floorx = -1.0f, floory = 0.0f, floorz = 0.0f;

     glm::mat4 floor_translateMatrix, floor_rotateXMatrix, floor_rotateYMatrix, floor_rotateZMatrix, floor_scaleMatrix, floor_fan_scaleMatrix, floor_model;
     floor_translateMatrix = glm::translate(identityMatrix, glm::vec3(floorx, floory - .0025f, floorz+0.3));
     floor_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
     floor_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
     floor_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
     floor_scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 0.01f, 6.0f));
     floor_model = floor_translateMatrix * floor_rotateXMatrix * floor_rotateYMatrix * floor_rotateZMatrix * floor_scaleMatrix;

     ourShader.setMat4("model", floor_model);

     glBindVertexArray(testVBO);
     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, testVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesTop), cube_verticesTop, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

       
     floor_translateMatrix = glm::translate(identityMatrix, glm::vec3(floorx, floory + 2.5, floorz + 0.3));
     floor_model = floor_translateMatrix * floor_rotateXMatrix * floor_rotateYMatrix * floor_rotateZMatrix * floor_scaleMatrix;

     ourShader.setMat4("model", floor_model);

     glBindVertexArray(testVBO);
     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

 

        //LRwall

     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, testVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesWall), cube_verticesWall, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);glBindVertexArray(VAO);
     

     float wallx = -1.0f, wally = 0.0f, wallz = 0.0f;

     glm::mat4 wall_translateMatrix, wall_rotateXMatrix, wall_rotateYMatrix, wall_rotateZMatrix, wall_scaleMatrix, wall_fan_scaleMatrix, wall_model;
     wall_translateMatrix = glm::translate(identityMatrix, glm::vec3(wallx-2.5, wally+1.25f , wallz + 0.3));
     wall_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
     wall_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
     wall_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
     wall_scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 5.0, 6.0f));
     wall_model = wall_translateMatrix * wall_rotateXMatrix * wall_rotateYMatrix * wall_rotateZMatrix * wall_scaleMatrix;

     ourShader.setMat4("model", wall_model);

     glBindVertexArray(testVBO);
     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


     wall_translateMatrix = glm::translate(identityMatrix, glm::vec3(wallx + 2.5, wally+ 1.25f, wallz + 0.3));
     wall_model = wall_translateMatrix * wall_rotateXMatrix * wall_rotateYMatrix * wall_rotateZMatrix * wall_scaleMatrix;

     ourShader.setMat4("model", wall_model);

     glBindVertexArray(testVBO);
     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



     //backWall

     glBindBuffer(GL_ARRAY_BUFFER, testVBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesBack), cube_verticesBack, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

     

     float backwallx = -1.0f, backwally = 0.0f, backwallz = 0.0f;

     glm::mat4 backwall_translateMatrix, backwall_rotateXMatrix, backwall_rotateYMatrix, backwall_rotateZMatrix, backwall_scaleMatrix, backwall_fan_scaleMatrix, backwall_model;
     backwall_translateMatrix = glm::translate(identityMatrix, glm::vec3(backwallx, backwally + 1.250f, backwallz - 1.2));
     backwall_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
     backwall_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
     backwall_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
     backwall_scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 5.0f, 0.01f));
     backwall_model = backwall_translateMatrix * backwall_rotateXMatrix * backwall_rotateYMatrix * backwall_rotateZMatrix * backwall_scaleMatrix;

     ourShader.setMat4("model", backwall_model);

     glBindVertexArray(testVBO);
     glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //For fan
        {   
            

         glBindBuffer(GL_ARRAY_BUFFER, testVBO);
         glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesCenter), cube_verticesCenter, GL_STATIC_DRAW);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            float fan_x= -1.0f, fan_y= 2.0f, fan_z=0.0f;

            glm::mat4 Fan_rotateYMatrix, fan_scaleMatrix, fan_model, fan_translateMatrix;
            fan_translateMatrix = glm::translate(identityMatrix, glm::vec3(fan_x, fan_y, fan_z));
            fan_scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, .01f, .1f));
            Fan_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(Fan_rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            fan_model = fan_translateMatrix * rotateXMatrix * Fan_rotateYMatrix * rotateZMatrix * fan_scaleMatrix;
            ourShader.setMat4("model", fan_model);

            glBindVertexArray(testVBO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            

            fan_scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, .01f, 3.0f));
            fan_model = fan_translateMatrix * rotateXMatrix * Fan_rotateYMatrix * rotateZMatrix * fan_scaleMatrix;
            ourShader.setMat4("model", fan_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesBlade), cube_verticesBlade, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            fan_scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.30f, 0.20f, 0.30f));
            fan_model = fan_translateMatrix * rotateXMatrix * Fan_rotateYMatrix * rotateZMatrix * fan_scaleMatrix;
            ourShader.setMat4("model", fan_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            if (fanIsOn) {
                Fan_rotateAngle_Y += 0.1f;
            }


            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            glBindVertexArray(testVBO);
            fan_translateMatrix = glm::translate(identityMatrix, glm::vec3(fan_x+0.0f, fan_y+.25f, fan_z+0.0f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
            model = fan_translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            ourShader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }
        

        //Axis line draw
        //{   
        //    translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        //    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        //    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        //    ourShader.setMat4("model", model);

        //    glUseProgram(ourShader.ID);
        //    glUniform3f(glGetUniformLocation(ourShader.ID, "lineColor"), 1.0f, 0.0f, 0.0f);  // Set line color (red)
        //    glBindVertexArray(axisVAO);
        //    glDrawArrays(GL_LINES, 0, 2);

        //    // Draw the y-axis line
        //    glUniform3f(glGetUniformLocation(ourShader.ID, "lineColor"), 0.0f, 1.0f, 0.0f);  // Set line color (green)
        //    glDrawArrays(GL_LINES, 2, 2);

        //    // Draw the z-axis line
        //    glUniform3f(glGetUniformLocation(ourShader.ID, "lineColor"), 0.0f, 0.0f, 1.0f);  // Set line color (blue)
        //    glDrawArrays(GL_LINES, 4, 2);
        //}
        
        
        //test 
        {
         /*
        glm::mat4 test_translateMatrix, test_rotateXMatrix, test_rotateYMatrix, test_rotateZMatrix, test_scaleMatrix, test_model;
            
        test_translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.1250, 0.0));
        test_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        test_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
        test_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        test_scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .5f, 2.0f));
        test_model = test_translateMatrix * test_rotateXMatrix * test_rotateYMatrix * test_rotateZMatrix * test_scaleMatrix;
        //test_rotaionY++;

        glBindVertexArray(testVAO);
        ourShader.setMat4("model", test_model);
        ourShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        */
        }


        //bed
        {   
            
            
            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesOrange), cube_verticesOrange, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            

            float bed_x = -1.0f, bed_y = 0.2f , bed_z = 0.0f;

            glm::mat4 bed_translateMatrix, bed_rotateXMatrix, bed_rotateYMatrix, bed_rotateZMatrix, bed_scaleMatrix, bed_model;

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x, bed_y, bed_z));
            bed_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            bed_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            bed_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .5f, 4.0f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


            //leg1

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x-0.5f, bed_y + 0.175f, bed_z - 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 1.5f, .25f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg2

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x + 0.5f, bed_y + 0.175f, bed_z - 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 1.5f, .25f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //leg3

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x + 0.5f, bed_y+ 0.05f, bed_z + 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 1.0f, .25f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg4

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x - 0.5f, bed_y+0.05f, bed_z + 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 1.0f, .25f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
          


            //Side1

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x , bed_y + 0.05f, bed_z + 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.1f, 0.99f, .15f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //Side2

            bed_translateMatrix = glm::translate(identityMatrix, glm::vec3(bed_x, bed_y + 0.175f, bed_z - 1.0f));
            bed_scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.1f, 1.49f, .2f));
            bed_model = bed_translateMatrix * bed_rotateXMatrix * bed_rotateYMatrix * bed_rotateZMatrix * bed_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", bed_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }


        //chair
        {  
            
            float chair_x = -2.3f, chair_y = 0.0f, chair_z = 0.0f;

   

            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            
            glm::mat4 chair_translateMatrix, chair_rotateXMatrix, chair_rotateYMatrix, chair_rotateZMatrix, chair_scaleMatrix, chair_model;

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x, chair_y + 0.48, chair_z));
            chair_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            chair_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            chair_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.7f, .2f, .7f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //backSide

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x + 0.145, chair_y + 0.84 , chair_z));
            chair_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.13f, 0.750f, .74f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            //test_rotaionY = test_rotaionY + .1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            //leg1

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x + 0.14, chair_y + 0.5, chair_z + 0.14));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 2.0f, .1f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg2

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x + 0.14, chair_y + 0.5, chair_z - 0.14));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 2.0f, .1f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg3

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x - 0.14, chair_y + 0.25, chair_z + 0.14));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg4

            chair_translateMatrix = glm::translate(identityMatrix, glm::vec3(chair_x - 0.14, chair_y + 0.25, chair_z - 0.14));
            chair_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            chair_model = chair_translateMatrix * chair_rotateXMatrix * chair_rotateYMatrix * chair_rotateZMatrix * chair_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", chair_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            


        }

        
        //tabel

        float table_x =  - 2.8f, table_y = 0.0f, table_z = 0.0f ;

        glBindBuffer(GL_ARRAY_BUFFER, testVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


        glm::mat4 table_translateMatrix, table_rotateXMatrix, table_rotateYMatrix, table_rotateZMatrix, table_scaleMatrix, table_model;

        table_translateMatrix = glm::translate(identityMatrix, glm::vec3(table_x, table_y+0.6880f , table_z));
        table_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        table_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
        table_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        table_scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.25f, 4.0f));
        table_model = table_translateMatrix * table_rotateXMatrix * table_rotateYMatrix * table_rotateZMatrix * table_scaleMatrix;
        //test_rotaionY = test_rotaionY+.1f;
        glBindVertexArray(testVAO);
        ourShader.setMat4("model", table_model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        glBindBuffer(GL_ARRAY_BUFFER, testVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

        //leg1

        table_translateMatrix = glm::translate(identityMatrix, glm::vec3(table_x + 0.43f, table_y + 0.375f , table_z + 0.93f));
        table_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, .2f));
        table_model = table_translateMatrix * table_rotateXMatrix * table_rotateYMatrix * table_rotateZMatrix * table_scaleMatrix;
        //test_rotaionY = test_rotaionY+.1f;
        glBindVertexArray(testVAO);
        ourShader.setMat4("model", table_model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //leg2

        table_translateMatrix = glm::translate(identityMatrix, glm::vec3(table_x + 0.43f, table_y + 0.375f, table_z - 0.93f));
        table_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, .2f));
        table_model = table_translateMatrix * table_rotateXMatrix * table_rotateYMatrix * table_rotateZMatrix * table_scaleMatrix;
        //test_rotaionY = test_rotaionY+.1f;
        glBindVertexArray(testVAO);
        ourShader.setMat4("model", table_model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //leg3

        table_translateMatrix = glm::translate(identityMatrix, glm::vec3(table_x - 0.43f, table_y + 0.375f, table_z + 0.93f));
        table_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, .2f));
        table_model = table_translateMatrix * table_rotateXMatrix * table_rotateYMatrix * table_rotateZMatrix * table_scaleMatrix;
        //test_rotaionY = test_rotaionY+.1f;
        glBindVertexArray(testVAO);
        ourShader.setMat4("model", table_model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //leg4

        table_translateMatrix = glm::translate(identityMatrix, glm::vec3(table_x - 0.43f, table_y + 0.375f, table_z - 0.93f));
        table_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.5f, .2f));
        table_model = table_translateMatrix * table_rotateXMatrix * table_rotateYMatrix * table_rotateZMatrix * table_scaleMatrix;
        //test_rotaionY = test_rotaionY+.1f;
        glBindVertexArray(testVAO);
        ourShader.setMat4("model", table_model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        


        {
            //TABLE 2

            
            
            float table2_x = 0.0f, table2_y = 0.0f, table2_z = -0.750f;



            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesSky), cube_verticesSky, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


            glm::mat4 table2_translateMatrix, table2_rotateXMatrix, table2_rotateYMatrix, table2_rotateZMatrix, table2_scaleMatrix, table2_model;
            //top
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x, table2_y + 0.5f, table2_z));
            table2_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            table2_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            table2_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.10f, 1.0f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            //Bottom 
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x, table2_y + 0.25f, table2_z));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            //leg1
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x + 0.215f, table2_y + 0.25f, table2_z - 0.215f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg1
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x + 0.215f, table2_y + 0.25f, table2_z + 0.215f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg2
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x - 0.215f, table2_y + 0.25f, table2_z - 0.215f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg3
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x - 0.215f, table2_y + 0.25f, table2_z + 0.215f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //leg4
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x + 0.215f, table2_y + 0.25f, table2_z - 0.215f));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.0f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



            glm::mat4 circle__translateMatrix, circle__rotateXMatrix, circle__rotateYMatrix, circle__rotateZMatrix, circle__scaleMatrix, circle__model;
            //Lamp_top
            float circle__x = 0.0f, circle__y = 0.0f, circle__z = 0.0f;

            circle__translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x, table2_y + 1.0f, table2_z));
            circle__rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            circle__rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            circle__rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            circle__scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
            circle__model = circle__translateMatrix * circle__rotateXMatrix * circle__rotateYMatrix * circle__rotateZMatrix * circle__scaleMatrix;


            glBindVertexArray(circle_VAO);
            ourShader.setMat4("model", circle__model);
            glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

            //stand
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x + 0.0f, table2_y + 0.75, table2_z - 0.0));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, .50f, .1f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //base
            table2_translateMatrix = glm::translate(identityMatrix, glm::vec3(table2_x + 0.0f, table2_y + 0.575, table2_z - 0.0));
            table2_scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.2f, 0.3f));
            table2_model = table2_translateMatrix * table2_rotateXMatrix * table2_rotateYMatrix * table2_rotateZMatrix * table2_scaleMatrix;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", table2_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }

        // render boxes
        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    // calculate the model matrix for each object and pass it to shader before drawing
        //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    ourShader.setMat4("model", model);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        // }


        {
            //almira
            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesGreen), cube_verticesGreen, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


            float Almira_x = 1.0f, Almira_y = 0.0f, Almira_z = 0.0f;

            glm::mat4 Almira_translateMatrix, Almira_rotateXMatrix, Almira_rotateYMatrix, Almira_rotateZMatrix, Almira_scaleMatrix, Almira_model;
            //top
            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x, Almira_y + 0.7f, Almira_z));
            Almira_rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            Almira_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(test_rotaionY), glm::vec3(0.0f, 1.0f, 0.0f));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 2.5f, 2.0f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x+0.19, Almira_y + 0.075, Almira_z+0.44));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(00.2f, 0.3f, 0.2f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x + 0.19, Almira_y + 0.075, Almira_z - 0.44));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(00.2f, 0.3f, 0.2f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x - 0.19, Almira_y + 0.075, Almira_z + 0.44));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(00.2f, 0.3f, 0.2f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x - 0.19, Almira_y + 0.075, Almira_z - 0.44));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(00.2f, 0.3f, 0.2f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesBlack), cube_verticesBlack, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x - 0.27, Almira_y + 0.7, Almira_z - 0.0));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(00.01f, 2.45f, 0.05f));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            //doors

            glBindBuffer(GL_ARRAY_BUFFER, testVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticesYello), cube_verticesYello, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

            Almira_translateMatrix = glm::translate(identityMatrix, glm::vec3(Almira_x - 0.17, Almira_y + 0.7, Almira_z - 0.0));
            Almira_rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            Almira_scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4, 2.45f, 1.9));
            Almira_model = Almira_translateMatrix * Almira_rotateXMatrix * Almira_rotateYMatrix * Almira_rotateZMatrix * Almira_scaleMatrix;
            //test_rotaionY = test_rotaionY+.1f;
            glBindVertexArray(testVAO);
            ourShader.setMat4("model", Almira_model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
 

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        fanIsOn = !fanIsOn;
    }


   

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
