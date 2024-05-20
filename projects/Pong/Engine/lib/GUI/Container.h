#pragma once
#include "Component.hpp"

namespace GUI
{
	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr;

	public:
		Container();

		void Pack(Component::Ptr component);
		bool IsSelectable() const override;

		void HandleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void Select(std::size_t index);
		void SelectNext();
		void SelectPrevious();
		bool HasSelection() const;

	private:
		std::vector<Component::Ptr> mChildren;
		int mSelectedChild;
	};
}
