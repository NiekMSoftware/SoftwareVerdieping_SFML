#include "GUI/Label.h"

namespace GUI
{
	Label::Label(const std::string& text, const FontHolder& fonts)
	: mText(text, fonts.Get(Fonts::DEFAULT), 16)
	{ }

	bool Label::IsSelectable() const
	{
		return false;
	}

	void Label::SetText(const std::string& text)
	{
		mText.setString(text);
	}

	void Label::HandleEvent(const sf::Event& event)
	{ }

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}
}
