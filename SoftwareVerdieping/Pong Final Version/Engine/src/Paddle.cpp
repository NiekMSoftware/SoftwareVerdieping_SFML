#include "Paddle.h"

Paddle::Paddle(float startX, float startY, const State::Context& context)
: GameObject(startX, startY, context),
paddleSpeed(5)
{
	mShape.setSize(sf::Vector2f(10, 80));
}

void Paddle::moveUp() {
	if (mPosition.y > 0) {
		mPosition.y -= paddleSpeed;
	}
}

void Paddle::moveDown() {
	if (mPosition.y + mShape.getSize().y < 600) {
		mPosition.y += paddleSpeed;
	}
}

void Paddle::updateObject() {
	mShape.setPosition(mPosition);
}
