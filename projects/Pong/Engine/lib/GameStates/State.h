#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceIdentifiers.inl"
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
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
		: window(&window),
		textures(&textures),
		fonts(&fonts)
		{
			printf("Instantiated Context.\n");
		}

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
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
