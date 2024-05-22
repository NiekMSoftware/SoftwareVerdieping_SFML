#include <cassert>
#include <States/StateStack.hpp>

StateStack::StateStack(const State::Context& context)
: mContext(context)
{ }

State::Ptr StateStack::CreateState(States::ID stateID)
{
	// find the state
	auto found = mFactories.find(stateID);

	// Assert the found state of the factory
	assert(found != mFactories.end());

	// Return the unique pointer of the found state
	return found->second();
}

void StateStack::Update(sf::Time dt)
{
	// Iterate through the stack
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		// Check if the smart pointer is Updating, if not return
		if (!(*itr)->Update(dt))
			return;
	}
}

void StateStack::FixedUpdate(sf::Time fixedDeltaTime)
{
	// Iterate through the stack
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		// Check if the smart pointer is Updating, if not return
		if (!(*itr)->FixedUpdate(fixedDeltaTime))
			return;
	}
}

void StateStack::Display()
{
	// Iterate through the stack
	for (const State::Ptr& ptr : mStack)
	{
		// Deref the Ptr to access state
		const State& state = *ptr;

		// Draw the State onto the screen
		state.Draw();
	}
}

void StateStack::HandleEvent(const sf::Event& event)
{
	// Iterate through stack
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		// check if the state should handle anything
		if (!(*itr)->HandleEvent(event))
			return;
	}
}

void StateStack::PushState(States::ID stateID)
{
	mPendingList.push_back({ PUSH, stateID });
}

void StateStack::PopState()
{
	mPendingList.push_back({ POP });
}

void StateStack::ClearStates()
{
	mPendingList.push_back({ CLEAR });
}

bool StateStack::IsEmpty() const
{
	return mStack.empty();
}

void StateStack::ApplyPendingChanges()
{
	// iterate through the pending changes
	for (const PendingChange change : mPendingList)
	{
		// Apply the changes if there are any
		switch (change.action)
		{
			case PUSH:
				mStack.push_back(CreateState(change.stateID));
				break;

			case POP:
				mStack.pop_back();
				break;

			case CLEAR:
				mStack.clear();
				break;
		}
	}

	// Clear out the pending list
	mPendingList.clear();
}