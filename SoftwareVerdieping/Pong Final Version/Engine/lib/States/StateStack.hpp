#pragma once

#include <functional>
#include <map>
#include <SFML/System/NonCopyable.hpp>

#include "State.hpp"
#include "StateIdentifiers.inl"

class State;

class StateStack : sf::NonCopyable
{
public:
	enum Actions
	{
		PUSH, //!< Push in a new State. 
		POP, //!< Pop the current State.
		CLEAR //!< Clear the stack of States.
	};

public:
	explicit StateStack(const State::Context& context);

	///////////////////////////////////////
	/// Registers a State with the given State ID.
	///
	/// \param stateID The ID of the State to register.
	///
	/////////////////////////////////////// 
	template <typename T>
	void RegisterState(States::ID stateID);

	void Update(sf::Time dt);
	void FixedUpdate(sf::Time fixedDt);
	void Display();
	void HandleEvent(const sf::Event& event);

	void PushState(States::ID stateID);
	void PopState();
	void ClearStates();

	// Returns either true or false based on the size of the container.
	bool IsEmpty() const;

	// Applies any pending changes from the pending list.
	void ApplyPendingChanges();

private:
	State::Ptr CreateState(States::ID stateID);

private:
	struct PendingChange
	{
		Actions action; //!< The action to perform.
		States::ID stateID; //!< The ID of the state.
	};

private:
	std::vector<State::Ptr> mStack; //!< The stack of the Unique pointers to the states.
	std::vector<PendingChange> mPendingList; //!< The pending list of the actions to perform on \c mStack.

	State::Context mContext; //!< The context shared among states.
	std::map<States::ID, std::function<State::Ptr()>> mFactories; //!< Factory for creating States.
};

template <typename T>
void StateStack::RegisterState(States::ID stateID)
{
	// Register a new state based upon the factory
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}