#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct TriangleVertex {
	float x, y, z;	//coordenadas
	float r, g, b;	//cores
};

bool readFile(const std::string& file, std::string& content) {
	std::string line;
	std::ifstream fileStream(file);

	if (!fileStream.is_open()) {
		std::cout << "Não foi possível abrir o arquivo: " << file << std::endl;
		return false;
	}

	content.clear();
	while (std::getline(fileStream, line)) {
		content += line + "\n";
	}

	return true;
}

bool isShaderCompiled(GLuint shaderId) {
	GLint compileStatus;
	const size_t logSize = 1000;
	GLchar log[logSize];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		glGetShaderInfoLog(shaderId, logSize, NULL, log);
		std::cout << "Shader compilation error log:" << log << std::endl;
		return false;
	}

	return true;
}

bool createShader(const std::string& shaderSource, GLenum shaderType, GLuint* shaderId) {
	GLuint shaderID;

	shaderID = glCreateShader(shaderType);

	const char* data = shaderSource.data();

	glShaderSource(shaderID, 1, &data, nullptr);
	glCompileShader(shaderID);

	if (isShaderCompiled(shaderID)) {
		*shaderId = shaderID;
		return true;
	}

	glDeleteShader(shaderID);

	return false;
}

bool isProgramLinked(GLuint programId) {
	GLint linkStatus;
	const size_t logSize = 1000;
	GLchar log[logSize];

	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

	if (!linkStatus) {
		glGetProgramInfoLog(programId, logSize, NULL, log);
		std::cout << "Program link error log:" << log << std::endl;
		return false;
	}

	return true;
}

bool createShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId, GLuint* shaderProgramId) {
	GLuint shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShaderId);
	glAttachShader(shaderProgramID, fragmentShaderId);
	glLinkProgram(shaderProgramID);

	if (isProgramLinked(shaderProgramID)) {
		*shaderProgramId = shaderProgramID;
		return true;
	}

	return false;
}

int main(void) {
	GLFWwindow* window;

	std::vector<TriangleVertex> vertices;
	GLuint bufferId;

	std::vector<unsigned int> indices;
	GLuint indicesId;

	GLuint vaoId;

	GLuint shaderProgram;
	GLuint vertexShader, fragmentShader;

	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	if (glfwInit() != GLFW_TRUE) {
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	//vértices
	vertices = {
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f }
	};

	//indices
	indices = { 0, 1, 2, 2, 3, 0 };

	//cria o buffer
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TriangleVertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indicesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//carrega os shaders
	if (!readFile("resources/shaders/vertex_shader.gl", vertexShaderSource) || !readFile("resources/shaders/fragment_shader.gl", fragmentShaderSource)) {
		glfwTerminate();
		return -1;
	}

	//cria os shaders
	if (!createShader(vertexShaderSource, GL_VERTEX_SHADER, &vertexShader) || !createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, &fragmentShader)) {
		glfwTerminate();
		return -1;
	}

	if (!createShaderProgram(vertexShader, fragmentShader, &shaderProgram)) {
		glfwTerminate();
		return -1;
	}

	glCreateVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), (const void*)(sizeof(float) * 3));

	glUseProgram(shaderProgram);

	glClearColor(0.6, 0.6, 0.0, 1.0);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vaoId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteBuffers(1, &bufferId);

	glfwTerminate();
	return 0;
}