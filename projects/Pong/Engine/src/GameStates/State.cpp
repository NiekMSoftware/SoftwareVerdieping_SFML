#include <GameStates/State.h>
#include "GameStates/StateStack.hpp"

State::State(StateStack& stack, const Context& context)
: mIsPaused(*context.paused),
mStack(&stack),
mContext(context)
{ }
State::~State() = default;

void State::RequestStackPush(States::ID stateID)
{
	mStack->PushState(stateID);
}

void State::RequestStackPop()
{
	mStack->PopState();
}

void State::RequestStateClear()
{
	mStack->ClearStates();
}

State::Context State::GetContext() const
{
	return mContext;
}