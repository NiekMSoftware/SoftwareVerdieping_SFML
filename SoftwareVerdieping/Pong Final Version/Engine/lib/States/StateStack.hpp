#pragma once

#include <functional>
#include <map>
#include <SFML/System/NonCopyable.hpp>

// include state files
#include "State.hpp"
#include "StateIdentifiers.inl"

class State;

////////////////////////////////////////
/// \brief Manages a stack of game states.
///
///	Providing mechanisms to push, pop and clear states.
///
////////////////////////////////////////
class StateStack : sf::NonCopyable
{
public:
	// The actions that can be performed on the state stack.
	enum Actions
	{
		PUSH, //!< Push in a new State. 
		POP, //!< Pop the current State.
		CLEAR //!< Clear the stack of States.
	};

public:
	////////////////////////////////////////
	/// \brief Constructs the StateStack with given context.
	///
	///	\param context The context shared among states.
	///
	///////////////////////////////////////
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

	////////////////////////////////////////
	/// \brief Updates the active states.
	///
	///	\param dt The time delta to update the states with.
	///
	////////////////////////////////////////
	void Update(sf::Time dt);

	////////////////////////////////////////
	/// \brief Updates the active states with fixed time steps.
	///
	///	\param fixedDt The fixed time delta to update the states with.
	///
	////////////////////////////////////////
	void FixedUpdate(sf::Time fixedDt);

	////////////////////////////////////////
	///
	/// \brief Renders the active states.
	///
	////////////////////////////////////////
	void Display() const;

	////////////////////////////////////////
	/// \brief Handles events for the active states.
	///
	///	\param event The SFML event to handle.
	///
	////////////////////////////////////////
	void HandleEvent(const sf::Event& event);

	////////////////////////////////////////
	/// \brief Pushes a state onto the stack.
	/// \param stateID The ID of the State to push.
	///
	////////////////////////////////////////
	void PushState(States::ID stateID);

	void PopState(); //!< Pops the current state from the stack.
	void ClearStates(); //!< Clears all states from the stack.

	////////////////////////////////////////
	///	\brief Checks if the stack is empty.
	///
	///	\returns True if the stack is empty, false otherwise.
	///
	////////////////////////////////////////
	bool IsEmpty() const;

	void ApplyPendingChanges(); //!< Applies any pending changes to the state stack.

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