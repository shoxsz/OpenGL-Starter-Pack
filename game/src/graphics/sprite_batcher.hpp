#ifndef _SPRITE_BATCHER_HPP_
#define _SPRITE_BATCHER_HPP_

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "texture.hpp"
#include "shader.hpp"
#include "buffer_object.hpp"
#include "vertex_array_object.hpp"

class SpriteBatcher{
public:
	struct VertexData {
		float x, y, z;
		float u, v;
	};

	static std::unique_ptr<SpriteBatcher> create(const std::string& vertexShader, const std::string& fragmentShader);

	SpriteBatcher(const SpriteBatcher& spriteBatcher) = delete;
	SpriteBatcher(SpriteBatcher&& spriteBatcher) = delete;

	void setProjection(const glm::mat4& projection);
	void setView(const glm::mat4& view);

	void begin();
	void end();

	void draw(TextureRegion* textureRegion, float width, float height, glm::mat4& transform);
	void draw(TextureRegion* textureRegion, const std::vector<VertexData>& vertices, const std::vector<unsigned int> indices, glm::mat4& transform);

private:
	SpriteBatcher() {}

	VertexData transformCoord(const VertexData& vertexData, glm::mat4& transform);

	TextureRegion* last = nullptr;

	glm::mat4 projection = glm::mat4(1);
	glm::mat4 view = glm::mat4(1);

	GLuint projectionLocation;
	GLuint viewLocation;
	GLuint textureLocation;

	const float z = 0;

	std::vector<VertexData> vertices;
	std::vector<unsigned int> indices;

	BufferObject verticesBuffer, indicesBuffer;
	VertexArrayObject vao;

	Program program;
	bool drawning = false;
};

#endif