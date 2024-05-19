#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"

namespace Textures
{
	enum Id
	{
		TITLE
	};
}

namespace Fonts
{
	enum Id
	{
		DEFAULT
	};
}

typedef ResourceHolder<sf::Font, Fonts::Id> FontHolder; //!< Type definition of the ResourceHolder as a FontHolder.
typedef ResourceHolder<sf::Texture, Textures::Id> TextureHolder; //!< Type definition of the ResourceHolder as a TextureHolder.