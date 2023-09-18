#define GLFW_INCLUDE_ES3

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <include/GLFW/glfw3.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
using namespace std;

const GLchar* vertexShaderSource[] = {
	"uniform mat4 uMVPMatrix;\n"
	"attribute vec4 aPosition;\n"
	"attribute vec2 aTexCoord;\n"
	"varying vec2 vTexCoord;\n"
	"void main() {\n"
		"gl_Position = uMVPMatrix * aPosition;\n"
		"vTexCoord = aTexCoord;\n"
	"}\n"
};

const GLchar* fragmentShaderSource[] = {
	"#extension GL_OES_EGL_image_external : require\n"
	"precision mediump float;\n"
	"uniform sampler2D sTexture;\n"
	"varying vec2 vTexCoord;\n"
	"void main() {\n"
    "   gl_FragColor = vec4(abs(vTexCoord.s), abs(vTexCoord.t), 1.0, 1.0);\n"
	"}\n"
};

float cubeVertices[] = {
    -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, -1, 1, 1, 1, -1, 1, -1, -1,
	1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1,
	-1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1,
	-1, -1, 1, -1, -1, -1, 1, -1, 1, 1, -1, -1,
	1, -1, -1, -1, 1, 1,
	-1, 1, 1, 1, 1, 1, -1, 1, -1, 1, 1, -1
};

float cubeTexCoords[] = {
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 1, 0, 0, 1, 1, 1, 0,
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 1, 0, 0, 1, 1, 1, 0,
	0, 1, 0, 0, 1, 1, 1, 0,
	1, 0, 0, 0,
	0, 0, 1, 0, 0, 1, 1, 1
};

struct ShaderHandler {
    GLuint aPosition;
    GLuint aTexCoord;
    GLuint mvMatrix;
    GLuint mvpMatrix;
};

struct Matrices {
    glm::mat4x4 modelView;
    glm::mat4x4 modelViewProjection;
};

GLuint shader;
ShaderHandler sh;
Matrices matrices;

int windowWidth = 640;
int windowHeight = 480;
glm::vec3 rotation;

inline float deg_to_rad(float rad) {
	return rad * float(M_PI / 180);
}

void errorfunc(int error, const char* description) {
    fputs(description, stderr);
}

void keyfunc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLuint compileShaders(const GLchar** vertexShaderSource, const GLchar** fragmentShaderSource)
{
	//Compile vertex shader
	GLuint vertexShader(glCreateShader(GL_VERTEX_SHADER));
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int logLength;
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1) {
		GLchar* strInfoLog = new GLchar[logLength + 1];
		glGetShaderInfoLog(vertexShader, logLength, NULL, strInfoLog);
		cout << "vertex shader error log:\n" << strInfoLog << "\n";
	};

	//Compile fragment shader
	GLuint fragmentShader(glCreateShader(GL_FRAGMENT_SHADER));
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	if (logLength > 1) {
		GLchar* strInfoLog = new GLchar[logLength + 1];
		glGetShaderInfoLog(fragmentShader, logLength, NULL, strInfoLog);
		cout << "fragment shader error log:\n" << strInfoLog << "\n";
	};

	//Link vertex and fragment shader together
	GLuint program(glCreateProgram());
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	//Delete shaders objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void initScene() {
    glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	shader = compileShaders(vertexShaderSource, fragmentShaderSource);
	glUseProgram(shader);    

	sh.aPosition = glGetAttribLocation(shader, "aPosition");
	sh.aTexCoord = glGetAttribLocation(shader, "aTexCoord");

	sh.mvpMatrix = glGetUniformLocation(shader, "uMVPMatrix");
	sh.mvMatrix = glGetUniformLocation(shader, "uMVMatrix");

	glVertexAttribPointer(sh.aPosition, 3, GL_FLOAT, false, 0, &cubeVertices);
	glVertexAttribPointer(sh.aTexCoord, 2, GL_FLOAT, false, 0, &cubeTexCoords);
	glEnableVertexAttribArray(sh.aPosition);
	glEnableVertexAttribArray(sh.aTexCoord);
}

void renderScene() {
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matrices.modelView = glm::mat4();
	matrices.modelView = glm::translate(matrices.modelView, glm::vec3(0.0f, 0.0f, -6.0f));
	matrices.modelView = glm::rotate(matrices.modelView, deg_to_rad(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	matrices.modelView = glm::rotate(matrices.modelView, deg_to_rad(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

	matrices.modelViewProjection = glm::perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f) * matrices.modelView;

	glUniformMatrix4fv(sh.mvpMatrix, 1, false, &matrices.modelViewProjection[0][0]);
	glUniformMatrix4fv(sh.mvMatrix, 1, false, &matrices.modelView[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 26);
}

int main() {
    GLFWwindow* window;
    glfwSetErrorCallback(errorfunc);

    if(!glfwInit()) {
        cout << "GLFW init failed.\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    window = glfwCreateWindow(600, 480, "ThinkReality OpenGLES", nullptr, nullptr);
    if(!window) {
        cout << "Window creation failed.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyfunc);
    initScene();

    while(!glfwWindowShouldClose(window)) {
        //glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor()
        //glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
        renderScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}