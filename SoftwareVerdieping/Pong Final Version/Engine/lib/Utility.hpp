#pragma once

#include <SFML/Graphics.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

template <typename Object>
void CenterOrigin(Object& object)
{
	sf::FloatRect bounds = object.getLocalBounds();
	object.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}