#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"

namespace Textures
{
	enum PlayerTextures
	{
		DEFAULT,
		INA,
		WOMP
	};
}

typedef ResourceHolder<sf::Texture, Textures::PlayerTextures> PlayerTextures;