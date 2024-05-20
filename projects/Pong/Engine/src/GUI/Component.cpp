#include "GUI/Component.hpp"

namespace GUI
{
	Component::Component()
	: mIsSelected(false),
	mIsActive(false)
	{ }

	Component::~Component()
	{ }

	bool Component::IsSelected() const
	{
		return mIsSelected;
	}

	bool Component::IsActive() const
	{
		return mIsActive;
	}

	void Component::Select()
	{ }

	void Component::Deselect()
	{ }

	void Component::Activate()
	{
		mIsActive = true;
	}

	void Component::Deactivate()
	{
		mIsActive = false;
	}
}