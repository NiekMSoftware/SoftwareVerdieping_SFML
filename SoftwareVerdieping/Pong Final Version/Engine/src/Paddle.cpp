#include "Paddle.h"

Paddle::Paddle(float startX, float startY)
: mPosition(startX, startY),
mShape(sf::Vector2f(10, 100)),
paddleSpeed(5) {
	// set the position of the paddle
	mShape.setPosition(mPosition);
}

sf::RectangleShape Paddle::getShape() const {
	return mShape;
}

void Paddle::moveUp() {
	mPosition.y -= paddleSpeed;
}

void Paddle::moveDown() {
	mPosition.y += paddleSpeed;
}

void Paddle::fixedUpdate() {
	mShape.setPosition(mPosition);
}
