#ifndef _BUFFER_OBJECT_HPP_
#define _BUFFER_OBJECT_HPP_

#include <gl/glew.h>

class BufferObject{
public:
	BufferObject(const BufferObject& buffer) = delete;
	BufferObject(BufferObject&& buffer) = delete;

	BufferObject(){}
	~BufferObject();

	void create(GLenum type);
	void bind();

	void setData(const void* data, GLsizeiptr size, GLenum usage);

	inline GLuint getId() const { return id; }
	inline GLenum getType() const { return type; }

private:
	GLuint id = 0;
	GLenum type = 0;
};

#endif