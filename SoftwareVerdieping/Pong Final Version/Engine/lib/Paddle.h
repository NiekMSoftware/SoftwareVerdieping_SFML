#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "ResourceIdentifiers.inl"
#include "States/State.hpp"

class State;

class Paddle : public GameObject {
public:
	Paddle(float startX, float startY, const State::Context& context);

	void moveUp();
	void moveDown();

	void updateObject() override;

private:
	// speed of paddle
	float paddleSpeed;
};
