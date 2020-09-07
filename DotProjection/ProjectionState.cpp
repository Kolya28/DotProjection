#include "pch.h"
#include "ProjectionState.h"

void ProjectionState::init(const sf::Vector2f& viewport)
{
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		throw std::runtime_error("Font Arial.ttf load error");

	coordText.setFont(font);
	pointPlaneText.setFont(font);

	pointPlaneText.setFillColor(sf::Color::Green);

	resizeCallback(viewport);
}

void ProjectionState::cleanup()
{
}

void ProjectionState::handleEvent(sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::TextEntered:
		if (ev.text.unicode == 13)
		{
			parseCoord(str);
			strClear = true;
			break;
		}

		if (strClear)
		{
			strClear = false;
			str.clear();
		}

		if (ev.text.unicode == 8)
		{
			if (str.empty())
				return;

			str.pop_back();
			return;
		}
		str += ev.text.unicode;
		break;
	}
}

void ProjectionState::update(float dt)
{
	coordText.setString(str);
}

void ProjectionState::draw(sf::RenderTarget& target)
{
	drawPoint(target);
	target.draw(coordText);
}

void ProjectionState::resizeCallback(const sf::Vector2f& viewport)
{
	scale.x = std::max(std::round(viewport.x / 100.f), 1.f);
	scale.y = std::max(std::round(viewport.y /  50.f), 1.f);


	coordText.setCharacterSize(2.5f * scale.x);

	coordText.setPosition(scale);

	pointPlaneText.setString("q");
	pointPlaneText.setCharacterSize(2 * scale.x);
	pointPlaneText.setOrigin(-scale.x, -scale.y);
}

void ProjectionState::parseCoord(const sf::String& str)
{
	std::stringstream ss(str);
	ss >> point.x >> point.y >> point.z;
}

void ProjectionState::drawPoint(sf::RenderTarget& target)
{
	sf::Vector2f size = static_cast<sf::Vector2f>(target.getSize());
	float lineThickness = std::max(std::min(scale.x, scale.y) / 15.f, 1.f);

	sf::RectangleShape line;
	line.setSize({ lineThickness, size.y });
	line.setPosition(size.x / 2.f - lineThickness / 2.f, 0.f);

	target.draw(line);

	line.setSize({ size.x, lineThickness });
	line.setPosition(0.f, size.y / 2.f - lineThickness / 2.f);
	target.draw(line);


	float maxCoord = std::max({ std::abs(point.x), std::abs(point.y), std::abs(point.z) });

	sf::Vector2f zero = size / 2.f;
	sf::Vector2f safezone = zero * 0.5f;

	float distribution = std::min((zero - safezone).x, (zero - safezone).y);

	sf::Vector3f normalizedPoint;
	normalizedPoint.x = point.x / maxCoord * distribution;
	normalizedPoint.y = point.y / maxCoord * distribution;
	normalizedPoint.z = point.z / maxCoord * distribution;

	sf::CircleShape pointShape;
	pointShape.setRadius(std::min(scale.x, scale.y)/2.f);
	pointShape.setFillColor(sf::Color::Red);

	//p2
	pointShape.setPosition(size.x - (normalizedPoint.x + zero.x), size.y - (normalizedPoint.z + zero.y));
	pointPlaneText.setString("2");
	pointPlaneText.setPosition(pointShape.getPosition());
	target.draw(pointShape);
	target.draw(pointPlaneText);

	//p3
	pointShape.setPosition((normalizedPoint.y + zero.x), size.y - (normalizedPoint.z + zero.y));
	pointPlaneText.setString("3");
	pointPlaneText.setPosition(pointShape.getPosition());
	target.draw(pointShape);
	target.draw(pointPlaneText);

	//p1
	pointShape.setPosition(size.x - (normalizedPoint.x + zero.x), (normalizedPoint.y + zero.y));
	pointPlaneText.setString("1");
	pointPlaneText.setPosition(pointShape.getPosition());
	target.draw(pointShape);
	target.draw(pointPlaneText);
}
