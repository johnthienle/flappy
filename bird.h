#pragma once

struct Bird {
	float x = 200.0f;
	float y = 300.0f;
	float width = 40.0f;
	float height = 40.0f;

	float velocity = 0.0f;
	float gravity = 500.0f;
	float jumpForce = 250.0f;

	void update(float deltaTime, float screenHeight) {
		velocity += gravity * deltaTime;
		y -= velocity * deltaTime;

		if (y < 0.0f) {
			y = 0.0f;
		}
		if (y + height > screenHeight) {
			y = screenHeight - height;
		}
	}

	void jump() {
		velocity = -jumpForce;
	}

	void updateYPosition(float pos) {
		y = pos;
	}
};