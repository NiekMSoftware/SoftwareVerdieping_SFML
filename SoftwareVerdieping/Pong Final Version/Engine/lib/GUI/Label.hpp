#pragma once

#include "Component.hpp"
#include "ResourceIdentifiers.inl"

namespace GUI
{
	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;

	public:
		Label(const std::string& text, const FontHolder& fonts);

		bool IsSelectable() const override;

		void SetText(const std::string& text);
		sf::Text& GetText();
		void SetSize(unsigned int size);

		void SetFont(const FontHolder& fonts, Fonts::Fonts id);

		void SetOutlineSize(float thickness);
		void SetOutlineColor(sf::Color color);

		void HandleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text mText;
	};
}