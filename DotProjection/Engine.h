#pragma once
#include "pch.h"
#include "State.h"
class State;

class Engine
{
public:
	static Engine& Instance()
	{
		static Engine instance;
		return instance;
	}

	void init();
	void cleanup();

	void pushState(State* state);
	void popState();
	void changeState(State* state);

	void poolEvents();
	void update(float dt);
	void draw();

	bool isRunning() { return window.isOpen(); }

private:
	void quit();
	Engine() {};

	std::deque<State*> states;
	sf::View defaultView;
	sf::RenderWindow window;
};

