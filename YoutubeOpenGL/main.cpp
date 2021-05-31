#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	// Initializes GLFW
	glfwInit();

	// Specifies the version of OpenGL to GLFW (OpenGL 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tells OpenGL to use only the CORE profile,
	// that has the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates a GLFWwindow object that is 800 by 800 pixels
	// and names it YoutubeOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

	// Checking if window failed to create and displaying an error message in cmd
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduces the Window into the current context
	glfwMakeContextCurrent(window);

	// Loads GLAD
	gladLoadGL();

	// Creates a viewport of OpenGL
	glViewport(0, 0, 800, 800);
	// Specifies background colour
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean back buffer and assign a colour to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swapping back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take care of any GLFW events
		glfwPollEvents();
	}

	// Destroy windiw before wnding program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}