#include "GUI/Container.h"

namespace GUI
{
	Container::Container()
	: mChildren(),
	mSelectedChild(-1)
	{ }

	void Container::Pack(Component::Ptr component)
	{
		mChildren.push_back(component);

		if (!HasSelection() && component->IsSelectable())
			Select(mChildren.size() - 1);
	}

	bool Container::IsSelectable() const
	{
		return false;
	}

	void Container::HandleEvent(const sf::Event& event)
	{
		// check if there is a valid selection and if the component is active
		if (HasSelection() && mChildren[mSelectedChild]->IsActive())
		{
			mChildren[mSelectedChild]->HandleEvent(event);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (HasSelection())
					mChildren[mSelectedChild]->Activate();
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			// otherwise get a valid selection and activate them
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				SelectPrevious();
			}
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				SelectNext();
			}
		}
	}

	void Container::Select(std::size_t index)
	{
		if (mChildren[index]->IsSelectable())
		{
			if (HasSelection())
				mChildren[mSelectedChild]->Deselect();

			mChildren[index]->Select();

			// cast the size_t to an int
			mSelectedChild = static_cast<int>(index);
		}
	}

	void Container::SelectNext()
	{
		if (!HasSelection())
			return;

		// search next component that is selectable
		int next = mSelectedChild;
		do
		{
			next = (next + 1) % static_cast<int>(mChildren.size());
		} while (!mChildren[next]->IsSelectable());

		Select(next);
	}

	void Container::SelectPrevious()
	{
		if (!HasSelection())
			return;

		// search next component that is selectable
		int prev = mSelectedChild;
		do
		{
			prev = (prev + static_cast<int>(mChildren.size()) - 1) % static_cast<int>(mChildren.size());
		} while (!mChildren[prev]->IsSelectable());

		Select(prev);
	}

	bool Container::HasSelection() const
	{
		return mSelectedChild >= 0;
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		// draw out all the children of the container
		for (const Component::Ptr& child : mChildren)
			target.draw(*child, states);
	}
}
