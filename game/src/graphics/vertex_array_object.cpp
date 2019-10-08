#include "vertex_array_object.hpp"

VertexArrayObject::~VertexArrayObject(){
	glDeleteVertexArrays(1, &vaoId);
}

void VertexArrayObject::create(){
	glGenVertexArrays(1, &vaoId);
}

void VertexArrayObject::bind(){
	glBindVertexArray(vaoId);
}

void VertexArrayObject::setAttribute(const AttributeLayout& attrib){
	glEnableVertexAttribArray(attrib.location);
	glVertexAttribPointer(
		attrib.location,
		attrib.components,
		attrib.type,
		GL_FALSE,
		attrib.stride,
		(const void*)(attrib.offset)
	);
}