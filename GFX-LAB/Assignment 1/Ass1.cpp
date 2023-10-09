#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
float rotateAngle = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"uniform vec3 triangleColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(triangleColor, 1.0f);\n"
"}\n\0";


int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1807037", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
-0.84,-0.0107,0,
-0.824,0.0189,0,
-0.802,0.0387,0,
-0.775,0.061,0,
-0.755,0.0832,0,
-0.724,0.103,0,
-0.695,0.123,0,
-0.662,0.135,0,
-0.625,0.148,0,
-0.599,0.155,0,
-0.562,0.168,0,
-0.529,0.177,0,
-0.498,0.175,0,
-0.472,0.18,0,
-0.435,0.18,0,
-0.414,0.18,0,
-0.37,0.18,0,
-0.332,0.18,0,
-0.292,0.176,0,
-0.262,0.178,0,
-0.227,0.178,0,
-0.207,0.181,0,
-0.184,0.183,0,
-0.157,0.178,0,
-0.134,0.178,0,
-0.116,0.179,0,
-0.0901,0.191,0,
0.0645,0.352,0,
0.118,0.389,0,
0.154,0.394,0,
0.203,0.401,0,
0.256,0.399,0,
0.3,0.389,0,
0.362,0.37,0,
0.427,0.343,0,
0.46,0.325,0,
0.695,0.193,0,
0.863,0.0823,0,
0.876,0.00093,0,
0.82,-0.0978,0,
0.789,-0.128,0,
0.755,-0.155,0,
0.724,-0.17,0,
0.684,-0.182,0,
0.654,-0.185,0,
0.628,-0.197,0,
0.62,-0.148,0,
0.61,-0.091,0,
0.591,-0.0614,0,
0.562,-0.0368,0,
0.518,-0.0147,0,
0.375,-0.0176,0,
0.337,-0.0473,0,
0.319,-0.0892,0,
0.315,-0.143,0,
0.314,-0.21,0,
0.314,-0.252,0,
-0.299,-0.258,0,
-0.31,-0.204,0,
-0.32,-0.175,0,
-0.334,-0.128,0,
-0.344,-0.0933,0,
-0.357,-0.0564,0,
-0.38,-0.0293,0,
-0.391,-0.00959,0,
-0.414,0.0125,0,
-0.446,0.0223,0,
-0.489,0.0272,0,
-0.528,0.0271,0,
-0.563,0.0122,0,
-0.598,-0.0101,0,
-0.62,-0.0348,0,
-0.63,-0.062,0,
-0.638,-0.109,0,
-0.642,-0.151,0,
-0.642,-0.193,0,
-0.669,-0.193,0,
-0.694,-0.178,0,
-0.721,-0.156,0,
-0.747,-0.134,0,
-0.773,-0.107,0,
-0.796,-0.0821,0,
-0.812,-0.0575,0,
-0.827,-0.0353,0,
0.84,-0.0107,0
 };

    float vertices2[] = { //first part fill
 -0.71,0.0028,0,
-0.646,-0.193,0,
-0.648,-0.171,0,
-0.648,-0.143,0,
-0.648,-0.119,0,
-0.643,-0.0891,0,
-0.638,-0.0694,0,
-0.633,-0.0472,0,
-0.622,-0.0299,0,
-0.609,-0.0151,0,
-0.596,0.00223,0,
-0.576,0.00475,0,
-0.56,0.00972,0,
-0.56,0.163,0,
-0.591,0.158,0,
-0.61,0.145,0,
-0.633,0.138,0,
-0.674,0.128,0,
-0.703,0.113,0,
-0.731,0.0956,0,
-0.758,0.0783,0,
-0.778,0.0659,0,
-0.793,0.0486,0,
-0.814,0.0313,0,
-0.827,0.0115,0,
-0.838,-0.0132,0,
-0.827,-0.0403,0,
-0.815,-0.0501,0,
-0.802,-0.0747,0,
-0.777,-0.0969,0,
-0.759,-0.124,0,
-0.747,-0.134,0,
-0.723,-0.156,0,
-0.707,-0.161,0,
-0.686,-0.183,0,
-0.664,-0.185,0,
-0.646,-0.193,0
    };

    float vertices3[] = {
 -0.428, 0.0890,0,
 -0.594,0.0047,0,
-0.596,0.0392,0,
-0.596,0.0664,0,
-0.596,0.0885,0,
-0.596,0.108,0,
-0.596,0.121,0,
-0.596,0.14,0,
-0.594,0.155,0,
-0.578,0.165,0,
-0.562,0.165,0,
-0.541,0.173,0,
-0.521,0.173,0,
-0.492,0.178,0,
-0.467,0.18,0,
-0.438,0.18,0,
-0.414,0.18,0,
-0.401,0.18,0,
-0.376,0.178,0,
-0.358,0.173,0,
-0.357,-0.0638,0,
-0.372,-0.0391,0,
-0.386,-0.0219,0,
-0.402,-0.00715,0,
-0.424,0.00759,0,
-0.445,0.0149,0,
-0.464,0.0223,0,
-0.487,0.0247,0,
-0.51,0.0246,0,
-0.526,0.0271,0,
-0.539,0.0246,0,
-0.552,0.0171,0,
-0.563,0.0122,0,
-0.594,0.0047,0,

    };


    float vertices4[] = {
        -0.282, -0.120,0,
        -0.454,0.0223,0,
-0.454,0.178,0,
-0.401,0.173,0,
-0.328,0.173,0,
-0.267,0.173,0,
-0.21,0.168,0,
-0.163,0.169,0,
-0.142,0.169,0,
-0.144,0.137,0,
-0.141,0.114,0,
-0.141,0.0921,0,
-0.137,0.0626,0,
-0.136,0.028,0,
-0.134,-0.00649,0,
-0.144,-0.0361,0,
-0.15,-0.0731,0,
-0.147,-0.0978,0,
-0.139,-0.132,0,
-0.134,-0.159,0,
-0.123,-0.184,0,
-0.112,-0.211,0,
-0.0953,-0.248,0,
-0.297,-0.251,0,
-0.308,-0.214,0,
-0.315,-0.187,0,
-0.321,-0.157,0,
-0.331,-0.135,0,
-0.344,-0.106,0,
-0.36,-0.0786,0,
-0.375,-0.0441,0,
-0.393,-0.0195,0,
-0.415,0.000213,0,
-0.435,0.015,0,
-0.454,0.0223,0


    };

    float vertices5[] = {
        0.172, 0.251,0,
        0.453,-0.00258,0,
0.458,0.32,0,
0.416,0.348,0,
0.385,0.36,0,
0.346,0.374,0,
0.31,0.379,0,
0.269,0.392,0,
0.23,0.391,0,
0.191,0.394,0,
0.157,0.389,0,
0.107,0.374,0,
0.0743,0.354,0,
0.0401,0.327,0,
0.0157,0.297,0,
-0.0104,0.263,0,
-0.0478,0.221,0,
-0.0754,0.198,0,
-0.0966,0.166,0,
-0.147,0.176,0,
-0.145,0.146,0,
-0.141,0.107,0,
-0.139,0.0724,0,
-0.142,-0.243,0,
0.314,-0.247,0,
0.314,-0.225,0,
0.311,-0.198,0,
0.31,-0.171,0,
0.31,-0.146,0,
0.313,-0.129,0,
0.318,-0.111,0,
0.323,-0.0917,0,
0.332,-0.0719,0,
0.344,-0.0571,0,
0.355,-0.0447,0,
0.365,-0.0373,0,
0.38,-0.0274,0,
0.389,-0.02,0,
0.409,-0.015,0,
0.428,-0.00757,0,
 0.453,-0.00258,0

    };

    float vrtx6[] = {
    -0.170, -0.0263,0,
    -0.258, 0.171,0.174,0,
-0.103, 0.171,0.174,0,
-0.0124, -0.250,0.173,0,
-0.251, -0.258,0.173,0,
-0.256, 0.171,-0.246,0
    };

    float vrtx7[] = {
        0.630, 0.0866,0,
        0.451,0.00482,0,
0.456,0.323,0,
0.503,0.303,0,
0.538,0.281,0,
0.59,0.254,0,
0.658,0.217,0,
0.703,0.185,0,
0.759,0.151,0,
0.809,0.119,0,
0.838,0.0995,0,
0.861,0.0847,0,
0.868,0.0527,0,
0.868,0.0256,0,
0.871,0.000918,0,
0.863,-0.0312,0,
0.853,-0.0558,0,
0.84,-0.0731,0,
0.825,-0.088,0,
0.807,-0.108,0,
0.797,-0.115,0,
0.781,-0.132,0,
0.765,-0.145,0,
0.741,-0.16,0,
0.719,-0.175,0,
0.701,-0.177,0,
0.685,-0.187,0,
0.661,-0.192,0,
0.646,-0.192,0,
0.632,-0.194,0,
0.63,-0.158,0,
0.625,-0.13,0,
0.62,-0.108,0,
0.612,-0.0737,0,
0.598,-0.0614,0,
0.589,-0.0491,0,
0.572,-0.0368,0,
0.554,-0.027,0,
0.528,-0.0197,0,
0.503,-0.0123,0,
0.482,-0.00744,0,
0.459,-0.0124,0,
0.451,-0.00998,0,
0.455,0.323,0,
 0.451,0.00482,0

    };

    //WHEEL

    float vrtx18[] = {
        -0.578,-0.181,0,
-0.577,-0.152,0,
-0.573,-0.125,0,
-0.562,-0.0933,0,
-0.551,-0.0718,0,
-0.533,-0.0528,0,
-0.515,-0.0396,0,
-0.493,-0.0313,0,
-0.472,-0.0348,0,
-0.456,-0.0347,0,
-0.436,-0.0478,0,
-0.421,-0.068,0,
-0.412,-0.087,0,
-0.4,-0.119,0,
-0.393,-0.159,0,
-0.392,-0.195,0,
-0.395,-0.23,0,
-0.407,-0.253,0,
-0.418,-0.273,0,
-0.433,-0.287,0,
-0.45,-0.307,0,
-0.481,-0.313,0,
-0.506,-0.311,0,
-0.534,-0.299,0,
-0.552,-0.276,0,
-0.559,-0.256,0,
-0.569,-0.232,0,
-0.573,-0.205,0,
-0.578,-0.181,0

    };

    float vrtx8[] = {
        -0.484, -0.173,0,
       -0.618,-0.184,0,
-0.618,-0.164,0,
-0.617,-0.143,0,
-0.613,-0.126,0,
-0.61,-0.105,0,
-0.606,-0.0863,0,
-0.599,-0.0732,0,
-0.591,-0.0553,0,
-0.583,-0.041,0,
-0.574,-0.0291,0,
-0.567,-0.016,0,
-0.556,-0.00407,0,
-0.542,0.00548,0,
-0.524,0.0138,0,
-0.508,0.0222,0,
-0.481,0.0211,0,
-0.465,0.0223,0,
-0.447,0.014,0,
-0.431,0.00575,0,
-0.413,-0.00728,0,
-0.4,-0.0251,0,
-0.385,-0.0477,0,
-0.376,-0.0762,0,
-0.366,-0.105,0,
-0.361,-0.143,0,
-0.356,-0.177,0,
-0.357,-0.212,0,
-0.363,-0.244,0,
-0.373,-0.281,0,
-0.382,-0.302,0,
-0.395,-0.312,0,
-0.407,-0.333,0,
-0.425,-0.355,0,
-0.446,-0.364,0,
-0.472,-0.368,0,
-0.496,-0.368,0,
-0.519,-0.368,0,
-0.536,-0.356,0,
-0.552,-0.344,0,
-0.567,-0.331,0,
-0.575,-0.318,0,
-0.588,-0.292,0,
-0.603,-0.266,0,
-0.612,-0.234,0,
-0.616,-0.214,0,
-0.618,-0.184,0


    };

    float vrtx9[] = {
        -0.463, -0.126,0,
        - 0.56,-0.0889,0,
-0.549,-0.0716,0,
-0.534,-0.0543,0,
-0.513,-0.042,0,
-0.492,-0.032,0,
-0.471,-0.0344,0,
-0.45,-0.0369,0,
-0.428,-0.0516,0,
-0.414,-0.0787,0,
-0.404,-0.101,0,
-0.396,-0.133,0,
-0.393,-0.165,0,
-0.391,-0.207,0,
-0.403,-0.239,0,
-0.422,-0.278,0,
-0.447,-0.306,0,
-0.471,-0.313,0,
-0.492,-0.318,0,
-0.515,-0.308,0,
-0.536,-0.294,0,
-0.552,-0.281,0,
-0.562,-0.262,0,
-0.567,-0.237,0,
-0.568,-0.114,0,
-0.573,-0.22,0,
-0.578,-0.197,0,
-0.578,-0.178,0,
-0.577,-0.158,0,
-0.577,-0.146,0,
-0.56,-0.0889,0


    };

    float vrtx10[] = {
        -0.495, -0.185,0,
        -0.508,-0.143,0,
-0.5,-0.131,0,
-0.49,-0.128,0,
-0.479,-0.128,0,
-0.471,-0.136,0,
-0.461,-0.143,0,
-0.456,-0.158,0,
-0.458,-0.173,0,
-0.461,-0.192,0,
-0.466,-0.202,0,
-0.479,-0.21,0,
-0.489,-0.207,0,
-0.502,-0.202,0,
-0.507,-0.192,0,
-0.513,-0.183,0,
-0.513,-0.165,0,
-0.513,-0.15,0,
-0.508,-0.143,0


    };

    //borber

    float vrtx11[] = {
        0.168, 0.236,0,
        -0.0234,0.176,0,
-0.00393,0.171,0,
0.0221,0.167,0,
0.0432,0.162,0,
0.0644,0.157,0,
0.0855,0.154,0,
0.108,0.154,0,
0.134,0.154,0,
0.162,0.155,0,
0.19,0.15,0,
0.216,0.145,0,
0.232,0.15,0,
0.251,0.162,0,
0.273,0.184,0,
0.286,0.204,0,
0.31,0.226,0,
0.328,0.256,0,
0.349,0.273,0,
0.354,0.293,0,
0.338,0.305,0,
0.317,0.315,0,
0.294,0.323,0,
0.269,0.33,0,
0.242,0.337,0,
0.209,0.337,0,
0.191,0.342,0,
0.17,0.344,0,
0.146,0.344,0,
0.13,0.347,0,
0.12,0.344,0,
-0.0234,0.176,0,
-0.0234,0.176,0

    };

    float vrtx12[] = {
        0.508, 0.239,0,
        0.456,0.316,0,
0.52,0.284,0,
0.583,0.249,0,
0.648,0.212,0,
0.687,0.188,0,
0.469,0.182,0,
0.448,0.182,0,
0.433,0.182,0,
0.427,0.19,0,
0.425,0.207,0,
0.429,0.229,0,
0.435,0.246,0,
0.445,0.281,0,
0.456,0.316,0

    };

    float vrtx13[] = {
   -0.812,0.0288,0,
-0.78,0.0634,0,
-0.752,0.0808,0,
-0.705,0.0957,0,
-0.484,0.121,0,
-0.238,0.136,0,
-0.00395,0.137,0,
0.206,0.125,0,

    };

    float vrtx14[] = { 
        -0.150, 0.181 ,0,
        -0.145,0.161,0,
-0.139,0.109,0,
-0.134,0.0527,0,
-0.134,0.00584,0,
-0.144,-0.0435,0,
-0.152,-0.0707,0,
-0.149,-0.103,0,
-0.139,-0.137,0,
-0.12,-0.186,0,
-0.0921,-0.248,0,
0.012,-0.25,0,
    };

    float vrtx15[] = { -0.0628,-0.194,0,
0.175,-0.193,0,
0.197,-0.193,0,
0.217,-0.186,0,
0.241,-0.176,0,
0.261,-0.134,0,
0.293,-0.0079,0,
    };

    float vrtx16[] = {
        0.228,0.0388,0,
0.245,0.0635,0,
0.266,0.0783,0,
0.3,0.103,0,
0.346,0.116,0,
0.394,0.123,0,
0.443,0.126,0,
0.547,0.111,0,
0.724,0.0795,0,
0.842,0.06,0,

    };

    float vrtx17[] = {
        0.850, -0.0928,0,
        0.806,-0.115,0,
0.835,-0.115,0,
0.864,-0.115,0,
0.866,-0.0854,0,
0.866,-0.0681,0,
0.843,-0.0707,0,
0.806,-0.115,0
    };

    //headlight

    float vrtx19[] = {
-0.805, -0.00349,0,
-0.827,-0.0392,0,
-0.813,-0.0416,0,
-0.798,-0.0403,0,
-0.786,-0.0415,0,
-0.786,-0.0284,0,
-0.786,-0.0142,0,
-0.787,0.00725,0,
-0.787,0.0215,0,
-0.787,0.0394,0,
-0.832,-0.0262,0,
-0.834,-0.00832,0,
-0.827,0.00121,0,
-0.815,0.0131,0,
-0.807,0.0227,0,
-0.798,0.0322,0,
-0.827,-0.0392,0
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 
    glBindVertexArray(VAO);


    

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

    unsigned int uniformColorLocation = glGetUniformLocation(shaderProgram, "triangleColor");
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    glLineWidth(7.0f);

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        
        glClearColor(.90f, 0.90f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glm::mat4 translationMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 scaleMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, 0.0f));
        rotationMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, 1.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        



        
        glUseProgram(shaderProgram);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_LINE_STRIP, 0,100);
        glBindVertexArray(0);


        
        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 37);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx8), vrtx8, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 47);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(.946f, .1f, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 47);
        glBindVertexArray(0);


        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_Y, translate_Y, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx9), vrtx9, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 31);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 1.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(.946f, .1f, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 31);
        glBindVertexArray(0);


        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_Y, translate_Y, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;


        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx10), vrtx10, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 19);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(.946f, .1f, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 19);
        glBindVertexArray(0);



        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx18), vrtx18, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 29);
        glBindVertexArray(0);


        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_Y, translate_Y, 0.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx18), vrtx18, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 29);
        glBindVertexArray(0);
        
        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 34);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 35);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 41);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx6), vrtx6, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx7), vrtx7, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 45);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx17), vrtx17, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
        glBindVertexArray(0);


        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 84);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx11), vrtx11, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 33);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx11), vrtx11, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 1, 32);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 1.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx12), vrtx12, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 15);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 1.0f, 1.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx19), vrtx19, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 17);
        glBindVertexArray(0);

        //borderlines

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx12), vrtx12, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 1, 14);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx13), vrtx13, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 8);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx14), vrtx14, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 12);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx15), vrtx15, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 7);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx16), vrtx16, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 10);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx17), vrtx17, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 1, 7);
        glBindVertexArray(0);

        glUniform3f(uniformColorLocation, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vrtx19), vrtx19, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 1, 16);
        glBindVertexArray(0);
        

        //=A1&","&B1&",0,"

       
        


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
   
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}