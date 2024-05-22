#include "States/State.hpp"

#include "States/StateStack.hpp"

State::State(StateStack& stateStack, const Context& context)
: mStack(&stateStack),
mContext(context)
{ }

State::~State() = default;

void State::RequestStackPush(States::ID id)
{
	mStack->PushState(id);
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
