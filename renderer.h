#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer(int screenWidth, int screenHeight);
	~Renderer();

	void beginScene();
	void drawRect(float x, float y, float w, float h, glm::vec3 color);

	GLuint shaderProgram;

private:
	GLuint VAO, VBO, EBO;
	int screenWidth, screenHeight;

	void setupShaders();
	void setupQuad();
	void setupProjection();
};