#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"
#include "States/State.hpp"

class GameObject : sf::Transformable {
public:
	GameObject(float startX, float startY, const State::Context& context);
	virtual ~GameObject();

	sf::RectangleShape getShape() const;
	void setTexture(Textures::PlayerTextures id);
	virtual void updateObject() = 0;

protected:
	sf::Vector2f mPosition;
	sf::RectangleShape mShape;

private:
	State::Context mContext;
};
