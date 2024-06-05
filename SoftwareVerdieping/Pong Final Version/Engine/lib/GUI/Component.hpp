#pragma once

#include <SFML/Graphics.hpp>

namespace GUI
{
	class Component : public sf::Transformable, public sf::Drawable, sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

	public:
		Component();
		virtual ~Component();

		virtual bool IsSelectable() const = 0;
		bool IsSelected() const;
		virtual bool IsActive() const;


		virtual void Select();
		virtual void Deselect();

		virtual void Activate();
		virtual void Deactivate();

		template<typename T>
		void CenterOrigin(T& object) const; //!< Centers the origin of an object.

		virtual void HandleEvent(const sf::Event& event) = 0;

	private:
		bool mIsSelected;
		bool mIsActive;
	};

	template <typename T>
	void Component::CenterOrigin(T& object) const
	{
		sf::FloatRect bounds = object.getLocalBounds();
		object.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	}
};