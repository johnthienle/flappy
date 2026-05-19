#pragma once
#include <cstdlib>
#include <random>

struct Pipe {
	float x = 800.0f;
	float width = 80.0f;
	float gapY = 360.0f;
	float gapSize = 125.0f;
	float speed = 200.0f;
	bool passed = false;

	void randomizeGap(int screenHeight) {
		float minY = 150.0f;
		float maxY = screenHeight - 150.0f;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(minY, maxY);
		gapY = distr(gen);
	}

	void passedPipe() {
		passed = true;
	}
};