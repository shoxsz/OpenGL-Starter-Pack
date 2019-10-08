#ifndef _VERTEX_ARRAY_OBJECT_HPP_
#define _VERTEX_ARRAY_OBJECT_HPP_

#include <gl/glew.h>

struct AttributeLayout{
	GLuint location;
	GLuint components;
	GLuint offset;
	GLuint stride;
	GLenum type;
};

class VertexArrayObject{
public:

	VertexArrayObject(const VertexArrayObject& vertex) = delete;
	VertexArrayObject(VertexArrayObject&& vertex) = delete;

	VertexArrayObject(){}
	~VertexArrayObject();

	void create();
	void bind();

	/** Bind this VAO, enable and set the attribute data from the currently bound BufferObject */
	void setAttribute(const AttributeLayout& attrib);

	const GLuint getId() const { return vaoId; }
private:
	GLuint vaoId = 0;
};

#endif