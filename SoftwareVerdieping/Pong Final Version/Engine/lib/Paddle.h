#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:
	Paddle(float startX, float startY);

	sf::RectangleShape getShape() const;

	void moveUp();
	void moveDown();

	void fixedUpdate();

private:
	// sfml properties
	sf::Vector2f mPosition; //!< position of the paddle
	sf::RectangleShape mShape; //!< rectangular shape of the paddle

	// speed of paddle
	float paddleSpeed;
};