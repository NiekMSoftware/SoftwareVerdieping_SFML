#pragma once
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

template <typename T>
void CenterOrigin(T& object)
{
	sf::FloatRect bounds = object.getLocalBounds();
	object.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}