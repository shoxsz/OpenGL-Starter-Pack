#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>
#include <string>

class Shader{
public:
	Shader(const Shader& shader) = delete;
	Shader(Shader&& shader) = delete;

	Shader(){}
	~Shader();

	bool create(GLenum type, const std::string& src);

	GLuint getId() const { return id; }
	GLenum getType() const { return type; }
private:

	bool isCompiled();

	GLuint id = 0;
	GLenum type = 0;
};

class Program{
public:
	Program(const Program& program) = delete;
	Program(Program&& program) = delete;

	Program(){}
	~Program();

	bool create(Shader& vertexShader, Shader& fragmentShader);

	void use();

	GLuint uniformLocation(const std::string& name);
	
	void loadUniform4x4(GLuint location, float* matrix);
	void loadUniform(GLuint location, GLint val);

private:
	bool isLinked();

	GLuint id = 0;
};

#endif