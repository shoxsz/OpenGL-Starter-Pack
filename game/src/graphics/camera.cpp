#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Camera::X = glm::vec3(1, 0, 0);
glm::vec3 Camera::Y = glm::vec3(0, 1, 0);
glm::vec3 Camera::Z = glm::vec3(0, 0, 1);

void Camera::setOrtho(float left, float right, float bottom, float top){
	projection = glm::ortho(left, right, bottom, top);
}

void Camera::setPersp(float fov, float ratio, float near, float far){
	projection = glm::perspective(fov, ratio, near, far);
}

void Camera::translate(float x, float y, float z){
	view = glm::translate(view, glm::vec3(x, y, z));
}

void Camera::setTranslation(float x, float y, float z){
	view = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
}

void Camera::rotate(float degrees, const glm::vec3& axis){
	view = glm::rotate(view, glm::radians(degrees), axis);
}

void Camera::setRotation(float degrees, const glm::vec3& axis){
	view = glm::rotate(glm::mat4(1), glm::radians(degrees), axis);
}
