#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

const char* vertexShaderSrc = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);"
"}\0";
const char* fragmentShaderSrc = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
	if (window == NULL)
	{
		cout << "Error:failed to create window !" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Error:failed to initialize GLAD" << endl;
		return -1;
	}
	glClearColor(0.2f, 0.3, 0.3f, 1);

	float positions[] = {
		0.5,-0.5,
		-0.5,0,
		-0.5,0.5
	};

	//Build
	//Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR: VERTEX_SHADER:" << infoLog << endl;
	}
	//Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR: FRAGMENT_SHADER:" << infoLog << endl;
	}
	//Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR: SHADER_PROGRAM:" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//VAO(Vertex Array Object)
	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	//copy to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	//ÉèÖÃ²½³¤
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClearColor(0.2f, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}