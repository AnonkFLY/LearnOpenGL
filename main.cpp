#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

int main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(666, 666, "Test", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed Create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}