#pragma once
#include <functional>

#include "Component.hpp"
#include "ResourceIdentifiers.inl"

namespace GUI
{
	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

	public:
		Button(const FontHolder& font, const TextureHolder& texture);

		void SetCallback(Callback callback);
		void SetToggle(bool flag);

		void SetText(const std::string& text);
		void SetTextColor(sf::Color color);
		void SetTextOutLineColor(sf::Color color);
		void SetTextOutLineThickness(float amount);

		bool IsSelectable() const override;
		void Select() override;
		void Deactivate() override;

		void Activate() override;
		void Deselect() override;

		void HandleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Callback mCallback;

		const sf::Texture& mNormalTexture;
		const sf::Texture& mSelectedTexture;
		const sf::Texture& mPressedTexture;

		sf::Sprite mSprite;
		sf::Text mText;

		bool mIsToggle;
	};
}
