#pragma once

#include "GameObject.hpp"
#include "ResourceIdentifiers.inl"
#include "States/State.hpp"

class State;

class Ball : public GameObject {
public:
	Ball(float startX, float startY, const State::Context& context);

	void updateObject() override;

	void reboundSides();
	void reboundBatOrTop();

	void reset(float startX, float startY);

private:
	float xVelocity;
	float yVelocity;

	const float maxVelocity;
};
