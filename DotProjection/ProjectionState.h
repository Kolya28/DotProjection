#pragma once
#include "pch.h"
#include "State.h"
class ProjectionState : public State
{
public:
	void init(const sf::Vector2f& viewport) override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw(sf::RenderTarget& target) override;

	void resizeCallback(const sf::Vector2f& viewport);

private:
	void parseCoord(const sf::String& str);
	void drawPoint(sf::RenderTarget& target);

	sf::Vector2f scale{ 1.f,1.f };
	sf::Font font;
	sf::Text coordText;
	sf::Text pointPlaneText;

	std::string str;
	float strClear = false;
	sf::Vector3f point{ 0.f,0.f,0.f };
};

