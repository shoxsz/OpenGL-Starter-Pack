#include "shader.hpp"

Shader::~Shader(){
	glDeleteShader(id);
}

bool Shader::create(GLenum type, const std::string& src){
	const char* data = src.data();

	id = glCreateShader(type);
	this->type = type;

	glShaderSource(id, 1, &data, nullptr);
	glCompileShader(id);

	if(!isCompiled()){
		id = 0;
		type = 0;
		return false;
	}

	return true;
}

bool Shader::isCompiled(){
	GLint compileStatus;
	const size_t logSize = 2048;
	GLchar log[logSize];

	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		glGetShaderInfoLog(id, logSize, NULL, log);
		return false;
	}

	return true;
}

Program::~Program(){
	glDeleteProgram(id);
}

bool Program::create(Shader& vertexShader, Shader& fragmentShader){
	id = glCreateProgram();
	glAttachShader(id, vertexShader.getId());
	glAttachShader(id, fragmentShader.getId());
	glLinkProgram(id);

	if(!isLinked()){
		id = 0;
		return false;
	}

	return true;
}

void Program::use(){
	glUseProgram(id);
}

GLuint Program::uniformLocation(const std::string& name){
	return glGetUniformLocation(id, name.c_str());
}

void Program::loadUniform4x4(GLuint location, float* matrix){
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Program::loadUniform(GLuint location, GLint val) {
	glUniform1i(location, val);
}

bool Program::isLinked(){
	GLint linkStatus;
	const size_t logSize = 2048;
	GLchar log[logSize];

	glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

	if (!linkStatus) {
		glGetProgramInfoLog(id, logSize, nullptr, log);
		return false;
	}

	return true;
}