#include "pch.h"
#include "Engine.h"

void Engine::init()
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	vm.height /= 2;
	vm.width /= 2;

	window.create(vm, "DotProjection", 7U, sf::ContextSettings(0, 0, 4));

	if (!window.isOpen())
		throw std::runtime_error("Window create error");

	defaultView = window.getDefaultView();
}

void Engine::cleanup()
{
	quit();
}

void Engine::pushState(State* state)
{
	state->init(defaultView.getSize());
	states.push_back(state);
}

void Engine::popState()
{
	states.back()->cleanup();
	delete states.back();
	states.pop_back();

	if (states.empty())
		quit();
}	

void Engine::changeState(State* state)
{
	if (states.empty())
		return;

	states.back()->cleanup();
	delete states.back();

	state->init(defaultView.getSize());
	states.back() = state;
}

void Engine::poolEvents()
{
	sf::Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Resized)
		{
			defaultView.setCenter(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
			defaultView.setSize(static_cast<sf::Vector2f>(window.getSize()));
			window.setView(defaultView);

			for (auto& s : states)
				s->resizeCallback(sf::Vector2f(ev.size.width, ev.size.height));

			continue;
		}

		if (ev.type == sf::Event::Closed)
		{
			quit();
			return;
		}

		for (auto& s : states)
			s->handleEvent(ev);
	}
}

void Engine::update(float dt)
{
	for (auto& s : states)
		s->update(dt);
}

void Engine::draw()
{
	window.clear();

	for (auto& s : states)
		s->draw(window);

	window.display();
}

void Engine::quit()
{
	window.close();

	while (!states.empty())
		popState();
}
