#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceIdentifiers.inl"
#include "StateIndentifier.inl"

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
		///	\param textures The textures of the States.
		///	\param fonts The fonts the States would need.
		///	\param paused Flag to check if the State's context is paused.
		/// 
		/////////////////////////////////////////////////////
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, bool& paused)
		: window(&window),
		textures(&textures),
		fonts(&fonts),
		paused(&paused)
		{
			printf("Instantiated Context.\n");
		}

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;

		bool* paused;
	};

public:
	State(StateStack& stack, const Context& context);
	virtual ~State();

	virtual void Draw() const = 0;
	virtual bool Update(sf::Time dt) = 0;
	virtual bool FixedUpdate(sf::Time fixedDt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	void RequestStackPush(States::Id stateID);
	void RequestStackPop();
	void RequestStateClear();

	Context GetContext() const;

	bool mIsPaused = false;

private:
	StateStack* mStack;
	
	Context mContext;
};