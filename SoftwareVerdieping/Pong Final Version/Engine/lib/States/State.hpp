#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"
#include "StateIdentifiers.inl"


class StateStack;

///////////////////////////////////////////
/// \brief Base class for all game states.
///
///	The State class serves as an abstract base class for different game states.
///	It provides a common interface for initializing, updating, rendering and handling events.
///	Each state is associated with a \c 'StateStack' and a shared context which includes access to the
///	render window and further important resources and data.
///
///////////////////////////////////////////
class State
{
public:
	typedef std::unique_ptr<State> Ptr; //!< Unique pointer to a State.

	/////////////////////////////////////////
	/// \brief Context shared among states.
	///
	///	This struct holds references to resources and other shared objects
	///	needed by states. It is passed to each state when it is created.
	///
	////////////////////////////////////////Gr
	struct Context
	{
		/////////////////////////////////////
		/// \brief Constructs the Context.
		///
		///	\param window Reference to the render window.
		///	\param textures Reference to the player textures.
		///	\param fonts Reference to the font holder.
		///	\param paused Reference to the pause flag.
		///
		/////////////////////////////////////
		Context(sf::RenderWindow& window, PlayerTextures& textures, FontHolder& fonts, bool& paused)
		: window(&window),
		textures(&textures),
		fonts(&fonts),
		paused(&paused)
		{ }

		sf::RenderWindow* window;	//!< Pointer to the render window.
		PlayerTextures* textures;	//!< Pointer to the player textures.
		FontHolder* fonts;			//!< Pointer to the font holder.

		bool* paused;				//!< Pointer to the pause flag.
	};

public:
	////////////////////////////////////////
	/// \brief Constructs a state with a given stack and context.
	///
	///	\param stack Reference to the state stack.
	///	\param context Reference to the shared context.
	///
	///////////////////////////////////////
	State(StateStack& stack, const Context& context);

	// Virtual destructor.
	virtual ~State();

	////////////////////////////////////////
	/// \brief Draws the state onto the render window.
	///
	///	This method must be implemented by derrived classes to draw the state's content.
	////////////////////////////////////////
	virtual void Draw() const = 0;

	////////////////////////////////////////
	/// \brief Updates the state.
	///
	///	\param dt The time delta for the update.
	///	\return True to continue updating, false to stop.
	///
	///////////////////////////////////////////
	virtual bool Update(sf::Time dt) = 0;

	////////////////////////////////////////
	/// \brief Performs a fixed update on the state.
	///
	///	\param fixedDt The fixed time delta for the update.
	///	\return True to continue updating, false to stop.
	///
	////////////////////////////////////////
	virtual bool FixedUpdate(sf::Time fixedDt) = 0;

	////////////////////////////////////////
	/// \brief Handles events for the state.
	///
	///	\param event The SFML event to handle.
	///	\return True if the event was handled, false otherwise.
	///
	////////////////////////////////////////
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	////////////////////////////////////////
	/// \brief Requests to push a new state onto the stack.
	///
	///	\param id The ID of the state to push.
	///
	////////////////////////////////////////
	void RequestStackPush(States::ID id);

	void RequestStackPop(); //!< Requests to pop the current state from the stack.
	void RequestStateClear(); //!< Requests to clear all states from the stack.

	////////////////////////////////////////
	/// \brief Gets the shared context.
	///
	///	\return The shared context.
	///
	////////////////////////////////////////
	Context GetContext() const;

	bool mIsPaused = false;		//!<  Indicates if the state is paused.

private:
	StateStack* mStack;		//!< Pointer to the state stack.

	Context mContext;	//!< Shared context for the state.
};