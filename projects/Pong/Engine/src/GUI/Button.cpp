#include "GUI/Button.h"

namespace GUI
{
	Button::Button(const FontHolder& font, const TextureHolder& texture) :
		mCallback(),
		mNormalTexture(texture.Get(Textures::DEFAULT)),
		mSelectedTexture(texture.Get(Textures::DEFAULT)),
		mPressedTexture(texture.Get(Textures::DEFAULT)),
		mText("", font.Get(Fonts::DEFAULT), 14),
		mIsToggle(false)
	{
	}

	void Button::SetCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::SetToggle(bool flag)
	{
		mIsToggle = flag;
	}

	void Button::SetText(const std::string& text)
	{
		mText.setString(text);
	}

	void Button::SetTextColor(sf::Color color)
	{
		mText.setFillColor(color);
	}

	void Button::SetTextOutLineColor(sf::Color color)
	{
		mText.setOutlineColor(color);
	}

	void Button::SetTextOutLineThickness(float amount)
	{
		mText.setOutlineThickness(amount);
	}

	bool Button::IsSelectable() const
	{
		return true;
	}

	void Button::Select()
	{
		Component::Select();

		mSprite.setTexture(mSelectedTexture);
	}

	void Button::Deactivate()
	{
		Component::Deactivate();

		if (mIsToggle)
		{
			// Reset texture to right one depending on if we are selected or not.
			if (IsSelected())
				mSprite.setTexture(mSelectedTexture);
			else
				mSprite.setTexture(mNormalTexture);
		}
	}

	void Button::Activate()
	{
		// If toggled we should show that the button is pressed.
		if (mIsToggle)
			mSprite.setTexture(mPressedTexture);

		if (mCallback)
			mCallback();

		// If we are not toggled then deactivate the button since we are just momentarily activated.
		if (!mIsToggle)
			Deactivate();
	}

	void Button::Deselect()
	{
		Component::Deselect();

		mSprite.setTexture(mNormalTexture);
	}

	void Button::HandleEvent(const sf::Event& event)
	{ }

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

}
