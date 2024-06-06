#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"

namespace Textures
{
	enum PlayerTextures
	{
		FUWAWA,
		BIJOU,
		NERISSA,
		SHIORIN
	};


}

namespace Fonts
{
	enum Fonts
	{
		DEFAULT_FONT,
		DEFAULT_BOLD
	};
}

typedef ResourceHolder<sf::Texture, Textures::PlayerTextures> PlayerTextures;
typedef ResourceHolder<sf::Font, Fonts::Fonts> FontHolder;