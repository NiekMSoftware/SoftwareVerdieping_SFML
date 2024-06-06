#include "GUI/Label.hpp"

namespace GUI
{
	Label::Label(const std::string& text, const FontHolder& fonts)
		: mText(text, fonts.get(Fonts::DEFAULT_FONT), 16)
	{ }

	bool Label::IsSelectable() const
	{
		return false;
	}

	void Label::SetText(const std::string& text)
	{
		mText.setString(text);
	}

	sf::Text& Label::GetText()
	{
		return mText;
	}

	void Label::SetSize(unsigned int size)
	{
		mText.setCharacterSize(size);
	}

	void Label::HandleEvent(const sf::Event& event)
	{ }

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::SetOutlineSize(float thickness)
	{
		mText.setOutlineThickness(thickness);
	}

	void Label::SetOutlineColor(sf::Color color)
	{
		mText.setOutlineColor(color);
	}
}