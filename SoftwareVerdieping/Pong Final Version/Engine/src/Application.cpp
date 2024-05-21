#include "Application.hpp"

Application::Application()
:mWindow(sf::VideoMode(800, 600), "Pong"),
mTimePerFrame(sf::seconds(1.f / 60)),
deltaTime(sf::Time::Zero),
fixedDeltaTime(sf::Time::Zero)
{ /* Setup needed resources and states. */ }

void Application::CalculateDeltaTimes()
{
	sf::Time elapsedTime = mClock.restart();
	deltaTime += elapsedTime;
	fixedDeltaTime += elapsedTime;
}

void Application::Run()
{
	while (mWindow.isOpen())
	{
		HandleEvent();
		CalculateDeltaTimes();

		while (fixedDeltaTime > mTimePerFrame)
		{
			HandleEvent();
			FixedUpdate(mTimePerFrame);
			fixedDeltaTime -= mTimePerFrame;
		}

		Update(deltaTime);
		Display();
	}
}

void Application::Update(sf::Time dt)
{
}

void Application::FixedUpdate(sf::Time fixedDt)
{
}

void Application::HandleEvent()
{
}

void Application::Display()
{
	mWindow.clear(sf::Color::Red);

	mWindow.display();
}
