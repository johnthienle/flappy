#include <game.h>
#include <glm/glm.hpp>
#include <cstdlib>
#include <random>
#include <iostream>

Game::Game(GLFWwindow* window, int screenWidth, int screenHeight)
	: window(window),
	renderer(screenWidth, screenHeight),
	screenWidth(screenWidth),
	screenHeight(screenHeight)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	if (!game) return;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		game->bird.jump();
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		std::cout << "High Score: " << game->highScore << "\n";
		game->restart();
	}
}

bool Game::isRunning() const {
	return !glfwWindowShouldClose(window);
}

void Game::restart() {
	gameOver = false;
	score = 0;
	bird.y = screenHeight / 2.0f;
	bird.velocity = 0.0f;
	pipes.clear();
	spawnTimer = 0.0f;
	lastTime = glfwGetTime();
	spawnPipe();
}

void Game::spawnPipe() {
	Pipe p;
	p.x = screenWidth;
	p.randomizeGap(screenHeight);
	pipes.push_back(p);
}

bool Game::detectCollision(Bird bird, Pipe pipe) {
	float bottomHeight = pipe.gapY - pipe.gapSize / 2.0f;
	float topStart = pipe.gapY + pipe.gapSize / 2.0f;
	float topHeight = screenHeight - topStart;

	bool topPipeCollision = bird.x < pipe.x + pipe.width &&
		bird.x + bird.width > pipe.x &&
		bird.y < topStart + topHeight &&
		bird.y + bird.height > topStart;

	bool bottomPipeCollision = bird.x < pipe.x + pipe.width &&
		bird.x + bird.width > pipe.x &&
		bird.y < bottomHeight &&
		bird.y + bird.height > 0.0f;

	return (topPipeCollision || bottomPipeCollision);
}

void Game::update() {
	if (gameOver) return;

	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	spawnTimer += deltaTime;
	if (spawnTimer >= spawnInterval) {
		spawnTimer = 0.0f;
		spawnPipe();
	}

	for (Pipe& pipe : pipes) {
		if (detectCollision(bird, pipe)) {
			gameOver = true;
		}

		if (!pipe.passed && bird.x > pipe.x + pipe.width) {
			pipe.passed = true;
			score++;
			if (score > highScore) {
				highScore = score;
			}
			std::cout << pipe.passed << "\n";
			std::cout << "Score: " << score << "\n";
		}

		pipe.x -= pipe.speed * deltaTime;
	}
	
	pipes.erase(
		std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) {return pipe.x + pipe.width < 0.0f;}),
		pipes.end()
	);

	bird.update(deltaTime, screenHeight);
}

void Game::render() {
	renderer.beginScene();

	//bird
	renderer.drawRect(bird.x, bird.y, bird.width, bird.height,
		glm::vec3(0.9f, 0.8f, 0.1f));

	for (const Pipe& pipe : pipes) {
		//bottom pipe
		float bottomHeight = pipe.gapY - pipe.gapSize / 2.0f;
		renderer.drawRect(pipe.x, 0.0f, pipe.width, bottomHeight,
			glm::vec3(0.2f, 0.8f, 0.2f));

		//top pipe
		float topStart = pipe.gapY + pipe.gapSize / 2.0f;
		float topHeight = screenHeight - topStart;
		renderer.drawRect(pipe.x, topStart, pipe.width, topHeight,
			glm::vec3(0.2f, 0.8f, 0.2f));
	}
}