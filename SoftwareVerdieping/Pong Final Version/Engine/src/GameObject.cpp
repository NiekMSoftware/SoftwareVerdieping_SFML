#include "GameObject.hpp"

GameObject::GameObject(const float startX, const float startY, const State::Context& context)
: mContext(context)
{
	mPosition.x = startX;
	mPosition.y = startY;

	mShape.setPosition(mPosition);
}

GameObject::~GameObject() = default;

sf::RectangleShape GameObject::getShape() const
{
	return mShape;
}

void GameObject::setTexture(const Textures::PlayerTextures id)
{
	const sf::Texture* texture = &mContext.textures->get(id);
	mShape.setTexture(texture);
}
