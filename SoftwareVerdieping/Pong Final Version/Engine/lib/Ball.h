#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(float startX, float startY);

	sf::CircleShape getShape() const;

	void fixedUpdate();

	void reboundSides();
	void reboundBatOrTop();

	void reset(float startX, float startY);

private:
	sf::Vector2f mPosition;
	sf::CircleShape mShape;

	float xVelocity;
	float yVelocity;

	const float maxVelocity;
};