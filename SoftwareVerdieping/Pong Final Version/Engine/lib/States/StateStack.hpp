#pragma once

#include <functional>
#include <map>
#include <SFML/System/NonCopyable.hpp>

// include state files
#include "State.hpp"
#include "StateIdentifiers.inl"

class State;

// Manages a stack of game states.
class StateStack : sf::NonCopyable
{
public:
	// The actions that can be performed on the stack.
	enum Actions
	{
		PUSH,
		POP,
		CLEAR
	};

public:
	explicit StateStack(const State::Context& context);

	////////////////////////////////////////
	/// \brief Registers a State with the given State ID.
	///
	/// \tparam T The type of the State to register.
	/// \param stateID The ID of the State to register.
	///
	////////////////////////////////////////
	template <typename T>
	void RegisterState(States::ID stateID);

	// Updates the active states.
	void Update(sf::Time dt);

	// Updates the active states with fixed time steps.
	void FixedUpdate(sf::Time fixedDt);

	// Renders out the stack's states.
	void Display() const;

	// Handles events for the active states.
	void HandleEvent(const sf::Event& event);

	void PushState(States::ID stateID);
	void PopState();
	void ClearStates();

	///	Checks if the stack is empty.
	///	\returns True if the stack is empty, false otherwise.
	bool IsEmpty() const;

	void ApplyPendingChanges();

private:
	////////////////////////////////////////
	/// \brief Creates a state based on its ID.
	///
	///	\param stateID The ID of the state to create.
	///	\returns A unique pointer to the newly created state.
	///
	////////////////////////////////////////
	State::Ptr CreateState(States::ID stateID);

private:
	// Represents a pending change to be applied to the state stack.
	struct PendingChange
	{
		Actions action;
		States::ID stateID;
	};

private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;

	State::Context mContext;

	// Factory for creating states.
	std::map<States::ID, std::function<State::Ptr()>> mFactories;
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