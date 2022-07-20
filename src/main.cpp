// Include GLFW

#include <iostream>

#include "Line.hpp"
#include "Cube.hpp"
#include "ResourceManager.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Angel.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

const unsigned int WIDTH = 728;
const unsigned int HEIGHT = 728;

GLFWwindow *InitWindow() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return nullptr;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
	               GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSwapInterval(1);

	// Open a window and create its OpenGL context
	GLFWwindow *window =
	    glfwCreateWindow(WIDTH, HEIGHT, "opengl-Red triangle", NULL, NULL);
	if (window == NULL) {
		fprintf(
		    stderr,
		    "Failed to open GLFW window. If you have an Intel GPU, they are "
		    "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to laod GLAD" << std::endl;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return window;
}

int main(void) {
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;
	Angel::init(WIDTH, HEIGHT);
	// Line l(0, 0, 200, 200, 5);
	Cube c(2);
	while (glfwWindowShouldClose(window) == false) {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Angel::drawAxes();
//		c.animate();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
