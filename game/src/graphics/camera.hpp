#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <glm/glm.hpp>

class Camera{
public:
	static glm::vec3 X;
	static glm::vec3 Y;
	static glm::vec3 Z;

	void setOrtho(float left, float right, float bottom, float top);
	void setPersp(float fov, float ratio, float near, float far);

	void translate(float x, float y, float z);
	void setTranslation(float x, float y, float z);

	void rotate(float degrees, const glm::vec3& axis);
	void setRotation(float degrees, const glm::vec3& axis);

	glm::mat4 view = glm::mat4(1);
	glm::mat4 projection = glm::mat4(1);
};

#endif