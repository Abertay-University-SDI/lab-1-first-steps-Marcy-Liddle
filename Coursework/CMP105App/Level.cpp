#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_snake.setRadius(10.0f);
	m_snake.setFillColor(sf::Color::Green);
	m_snake.setPosition({ 300,300 });
	
	

}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		m_direction = Direction::RIGHT;
	}


	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		m_direction = Direction::LEFT;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		m_direction = Direction::UP;
	}


	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_direction = Direction::DOWN;
	}
}

// Update game objects
void Level::update(float dt)
{
	switch(m_direction)
	{
		case Direction::UP:
			m_snake.move({0.f, -m_speed * dt});
			break;

		case Direction::DOWN:
			m_snake.move({0.f, m_speed * dt});
			break;

		case Direction::LEFT:
			m_snake.move({ -m_speed * dt, 0.f });
			break;

		case Direction::RIGHT:
			m_snake.move({ m_speed * dt, 0.f });
			break;

		default:
			break;
	}

	sf::Vector2f pos = m_snake.getPosition();
	float radius = m_snake.getRadius();

	sf::Vector2u window_Size = m_window.getSize();

	if (pos.x > window_Size.x - radius ||  pos.x < 0)
	{
		m_snake.setPosition({ window_Size.x * 0.5f, window_Size.y * 0.5f });
	}
	if (pos.y > window_Size.y - radius || pos.y < 0)
	{
		m_snake.setPosition({ window_Size.x * 0.5f, window_Size.y * 0.5f });
	}
}

// Render level
void Level::render()
{
	beginDraw();

	m_window.draw(m_snake);

	endDraw();
}

