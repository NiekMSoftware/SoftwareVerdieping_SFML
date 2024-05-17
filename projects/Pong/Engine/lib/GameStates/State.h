#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "StateIdentifiers.inl"

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	// Context of State
	struct Context
	{
		/////////////////////////////////////////////////////
		/// Constructor of Context, this constructs all the context the states would need.
		///
		/// \param window The window of the State.
		/// 
		/////////////////////////////////////////////////////
		Context(sf::RenderWindow& window)
		: window(&window)
		{
			printf("Instantiated Context.");
		}

		sf::RenderWindow* window;
	};

public:
	State(StateStack& stack, const Context& context);
	virtual ~State();

	virtual void Draw() const = 0;
	virtual bool Update(sf::Time dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	void RequestStackPush(States::ID stateID);
	void RequestStackPop();
	void RequestStateClear();

	Context GetContext() const;

private:
	StateStack* mStack;
	
	Context mContext;
};
