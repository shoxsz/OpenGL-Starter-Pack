#include "sprite_batcher.hpp"

#include "helpers/files.hpp"

#include <glm/gtc/type_ptr.hpp>

std::unique_ptr<SpriteBatcher> SpriteBatcher::create(const std::string& vertexShader, const std::string& fragmentShader){
	std::unique_ptr<SpriteBatcher> batcher(new SpriteBatcher());
	Shader vertex, fragment;
	std::string vertexSrc, fragmentSrc;

	if(!Files::loadContents(vertexShader, vertexSrc) || !Files::loadContents(fragmentShader, fragmentSrc)){
		return nullptr;
	}

	if(!vertex.create(GL_VERTEX_SHADER, vertexSrc) || !fragment.create(GL_FRAGMENT_SHADER, fragmentSrc)){
		return nullptr;
	}

	if(!batcher->program.create(vertex, fragment)){
		return nullptr;
	}

	batcher->verticesBuffer.create(GL_ARRAY_BUFFER);
	batcher->indicesBuffer.create(GL_ELEMENT_ARRAY_BUFFER);
	batcher->vao.create();

	batcher->projectionLocation = batcher->program.uniformLocation("projection");
	batcher->viewLocation = batcher->program.uniformLocation("view");
	batcher->textureLocation = batcher->program.uniformLocation("tex");

	return batcher;
}

void SpriteBatcher::setProjection(const glm::mat4& projection){
	this->projection = projection;
}

void SpriteBatcher::setView(const glm::mat4& view){
	this->view = view;
}

void SpriteBatcher::begin(){
	if(!drawning){
		drawning = true;
		last = nullptr;

		vertices.clear();
		indices.clear();
	}
}

SpriteBatcher::VertexData SpriteBatcher::transformCoord(const VertexData& vertexData, glm::mat4& transform){
	glm::vec4 result = transform * glm::vec4(vertexData.x, vertexData.y, vertexData.z, 1);
	return { result.x, result.y, result.z, vertexData.u, vertexData.v};
}

void SpriteBatcher::draw(TextureRegion* textureRegion, float width, float height, glm::mat4& transform){
	if (!drawning) return;

	if (last != nullptr && last->texture != textureRegion->texture) {
		end();
		begin();
	}

	last = textureRegion;

	unsigned int startIdx = vertices.size();
	VertexData transformed;

	vertices.push_back(transformCoord({ 0, 0, z, textureRegion->u, textureRegion->v }, transform));
	vertices.push_back(transformCoord({ width, 0, z, textureRegion->u2, textureRegion->v }, transform));
	vertices.push_back(transformCoord({ width, height, z, textureRegion->u2, textureRegion->v2 }, transform));
	vertices.push_back(transformCoord({ 0, height, z, textureRegion->u, textureRegion->v2 }, transform));

	indices.push_back(startIdx);
	indices.push_back(startIdx + 1);
	indices.push_back(startIdx + 2);
	indices.push_back(startIdx + 2);
	indices.push_back(startIdx + 3);
	indices.push_back(startIdx);
}


void SpriteBatcher::draw(TextureRegion* textureRegion, const std::vector<VertexData>& vertices, const std::vector<unsigned int> indices, glm::mat4& transform) {
	if (!drawning) return;

	if (last != nullptr && last->texture != textureRegion->texture) {
		end();
		begin();
	}

	last = textureRegion;

	for (const VertexData& vertex : vertices) {
		this->vertices.push_back(transformCoord(vertex, transform));
	}

	for (unsigned int indice : indices) {
		this->indices.push_back(indice);
	}
}

void SpriteBatcher::end(){
	if(drawning && vertices.size() > 0){
		vao.bind();

		verticesBuffer.bind();
		verticesBuffer.setData(vertices.data(), vertices.size() * sizeof(VertexData), GL_STATIC_DRAW);
		
		//coords
		vao.setAttribute({
			0,
			3,
			0,
			sizeof(VertexData),
			GL_FLOAT
			});

		indicesBuffer.bind();
		indicesBuffer.setData(indices.data(), indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

		//texture coords
		vao.setAttribute({
			1,
			2,
			sizeof(float) * 3,
			sizeof(VertexData),
			GL_FLOAT
			});

		last->texture->bind();

		program.use();
		program.loadUniform4x4(projectionLocation, glm::value_ptr(projection));
		program.loadUniform4x4(viewLocation, glm::value_ptr(view));
		program.loadUniform(textureLocation, 0);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

		drawning = false;
	}
}