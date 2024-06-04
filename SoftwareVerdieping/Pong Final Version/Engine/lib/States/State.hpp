#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"
#include "StateIdentifiers.inl"

// forward decleration to the stackz
class StateStack;

// Base class for all game states.
class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	// Context shared amongst states.
	struct Context
	{
		Context(sf::RenderWindow& window, PlayerTextures& textures, FontHolder& fonts, bool& paused)
		: window(&window),
		textures(&textures),
		fonts(&fonts),
		paused(&paused)
		{ }

		sf::RenderWindow* window;
		PlayerTextures* textures;
		FontHolder* fonts;

		bool* paused;
	};

public:
	State(StateStack& stack, const Context& context);

	virtual ~State();

	// Draws out the state to the render window
	virtual void Draw() const = 0;

	/// Updates the state.
	///	\return True to continue updating, false to stop.
	virtual bool Update(sf::Time deltaTime) = 0;

	/// Performs a fixed update with the given fixed delta time.
	///	\return True to continue updating, false to stop.
	virtual bool FixedUpdate(sf::Time fixedDeltaTime) = 0;

	/// Handles events for the state.
	///	\return True if the event was handled, false if not.
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	void RequestStackPush(States::ID id);

	void RequestStackPop();
	void RequestStateClear();

	Context GetContext() const;

	bool& mIsPaused;

private:
	StateStack* mStack;

	Context mContext;
};