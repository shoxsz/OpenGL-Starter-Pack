#include "buffer_object.hpp"

void BufferObject::create(GLenum type){
	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	this->type = type;
}

BufferObject::~BufferObject(){
	glDeleteBuffers(1, &id);
}

void BufferObject::bind(){
	glBindBuffer(type, id);
}

void BufferObject::setData(const void* data, GLsizeiptr size, GLenum usage){
	glBufferData(type, size, data, usage);
}
