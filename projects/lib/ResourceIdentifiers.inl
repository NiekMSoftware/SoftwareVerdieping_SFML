#pragma once
#include <SFML/Graphics/Font.hpp>

#include "ResourceHolder.hpp"

namespace Fonts
{
	enum ID
	{
		Default
	};
}

namespace Textures
{
	enum ID
	{
		Title
	};
}

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder; //!< Type definition of the ResourceHolder as a FontHolder.
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder; //!< Type definition of the ResourceHolder as a TextureHolder.