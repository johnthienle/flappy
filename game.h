#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Bird.h"
#include "Pipe.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


class Game {
public:
	Game(GLFWwindow* window, int screenWidth, int screenHeight);

	void update();
	void render();
	void restart();

	bool isRunning() const;

	int highScore = 0;

	Bird bird;

private:
	GLFWwindow* window;
	Renderer renderer;
	std::vector<Pipe> pipes;

	void spawnPipe();
	bool detectCollision(Bird bird, Pipe pipe);

	int screenWidth;
	int screenHeight;

	int score = 0;
	bool gameOver = false;

	float lastTime = 0.0f;
	float spawnInterval = 2.0f;
	float spawnTimer = 0.0f;
};