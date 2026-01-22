#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_snake.setRadius(10.0f);
	m_snake.setFillColor(sf::Color::Green);
	m_snake.setPosition({ 300,300 });
	
	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Red);
	spawnFood();

	m_gameOver = false;

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
		;
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
	//stops updating when game over
	if (m_gameOver) { return;}

	m_timer += dt;     // add to the timer
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
		//m_snake.setPosition({ window_Size.x * 0.5f, window_Size.y * 0.5f });
		// wall hit -> game over
		m_gameOver = true;
		std::cout << "GAME OVER\n" << "Score: " << m_score;
		std::cout << "\nTime: " << m_timer << " seconds\n";

	}
	else if (pos.y > window_Size.y - radius || pos.y < 0)
	{
		//m_snake.setPosition({ window_Size.x * 0.5f, window_Size.y * 0.5f });

		// wall hit -> game over
		m_gameOver = true;
		std::cout << "GAME OVER\n" << "Score: " << m_score;
		std::cout << "\nTime: " << m_timer << " seconds\n";
	}


	//food collision
	float x_dist = (pos.x + radius) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (pos.y + radius) - (m_food.getPosition().y + m_food.getRadius());

	float squared_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float radii_sum = radius + m_food.getRadius();
	if (squared_dist < radii_sum * radii_sum)
	{
		// they are colliding
		spawnFood();
		m_speed *= 1.1f;
		m_score += 1;
	}
}


void Level::spawnFood()
{
	// position of the middle of the snake
	sf::Vector2f pos = m_snake.getPosition() + sf::Vector2f(m_snake.getRadius(), m_snake.getRadius());

	float x = rand() % m_window.getSize().x;
	float y = rand() % m_window.getSize().y;
	
	float min_dist = std::min(m_window.getSize().x * 0.25f, m_window.getSize().y * 0.25f);


	while (abs(x - pos.x + m_food.getRadius()) <= min_dist && abs(y - pos.y + m_food.getRadius()) <= min_dist)
	{
		x = rand() % m_window.getSize().x;
		y = rand() % m_window.getSize().y;
	}

	m_food.setPosition({ x , y});
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_food);
	m_window.draw(m_snake);
	

	endDraw();
}

