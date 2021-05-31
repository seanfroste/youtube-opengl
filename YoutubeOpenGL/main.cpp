#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader Source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	// Initializes GLFW
	glfwInit();

	// Specifies the version of OpenGL to GLFW (OpenGL 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tells OpenGL to use only the CORE profile,
	// that has the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Specifying triangle vertices
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // top vertex
	};

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

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader Source (from the start of the program)
	// to the Vertex Shader Object we just created
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader Source (from the start of the program)
	// to the Fragment Shader Object we just created
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get reference
	GLuint shaderProgram = glCreateProgram();
	// Attach Vertex Shader and Fragment Shader to the newly created program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete Vertex and Fragment Shader Objects, since they are already compiled
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate VAO and VBO, with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind (make current) the Vertex Array Object
	glBindVertexArray(VAO);

	// Bind (make current) the Vertex Buffer Object
	// (specify that it is a GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure Vertex Attribute to specify how OpenGL should read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable Vertex Attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	// Bind VAO and VBO to 0 to prevent us from accidentally modifying it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specifies background colour
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean back buffer and assign a colour to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swapping back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Specify the Shader Program to be used by OpenGL
		glUseProgram(shaderProgram);
		// Bind VAO
		glBindVertexArray(VAO);
		//Draw Triangle using current (bound) arrays
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Take care of any GLFW events
		glfwPollEvents();
	}

	// Delete all created objects to prepare the program for termination
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroy window in memory before ending program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}