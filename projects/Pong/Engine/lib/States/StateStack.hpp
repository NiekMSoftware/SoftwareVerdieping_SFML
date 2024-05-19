#pragma once

#include <functional>
#include <map>
#include <SFML/System/NonCopyable.hpp>

#include "State.hpp"
#include "StateIndentifier.inl"

// Forward declaration of State.
class State;

class StateStack : sf::NonCopyable
{
public:
	enum Actions
	{
		Push, //!< Push in a new State. 
		Pop, //!< Pop the current State.
		Clear //!< Clear the stack of States.
	};

public:
	explicit StateStack(State::Context context);

	///////////////////////////////////////
	/// Registers a State with the given State ID.
	///
	/// \param stateID The ID of the State to register.
	///
	/////////////////////////////////////// 
	template <typename T>
	void RegisterState(States::Id stateID);

	void Update(sf::Time dt);
	void FixedUpdate(sf::Time fixedDeltaTime);
	void Display();
	void HandleEvent(const sf::Event& event);

	void PushState(States::Id stateID);
	void PopState();
	void ClearStates();

	// Returns either true or false based on the size of the container.
	bool IsEmpty() const;

	// Applies any pending changes from the pending list.
	void ApplyPendingChanges();
	
private:
	State::Ptr CreateState(States::Id stateID);

private:
	struct PendingChange
	{
		Actions action; //!< The action to perform.
		States::Id stateID; //!< The ID of the state.
	};

private:
	std::vector<State::Ptr> mStack; //!< The stack of the Unique pointers to the states.
	std::vector<PendingChange> mPendingList; //!< The pending list of the actions to perform on \c mStack.
	
	State::Context mContext; //!< The context shared among states.
	std::map<States::Id, std::function<State::Ptr()>> mFactories; //!< Factory for creating States.
};

template <typename T>
void StateStack::RegisterState(States::Id stateID)
{
	// Register a new state based upon the factory
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));	
	};
}