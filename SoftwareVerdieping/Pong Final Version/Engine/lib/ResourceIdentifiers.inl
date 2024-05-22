#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"

namespace Textures
{
	enum PlayerTextures
	{
		DEFAULT,
		INA,
		WOMP,
		TEXTURE_COUNT
	};

	enum Fonts
	{
		DEFAULT_FONT
	};
}

typedef ResourceHolder<sf::Texture, Textures::PlayerTextures> PlayerTextures;
typedef ResourceHolder<sf::Font, Textures::Fonts> FontHolder;