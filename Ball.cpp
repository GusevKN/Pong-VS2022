#include "Ball.h"
// ‘ункци€-конструктор
Ball::Ball(float startX, float startY) : m_Position(startX, startY)
{
	m_Shape.setSize(sf::Vector2f(30, 30));
	m_Shape.setPosition(m_Position);
}
FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}
RectangleShape Ball::getShape()
{
	return m_Shape;
}
float Ball::getXVelocity()
{
	return m_DirectionX;
}
void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}
void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;
}
void Ball::reboundBottom()
{
	m_Position.y = 0;
	m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
}
void Ball::update(Time dt)
{
	// ќбновл€ем позицию м€ча
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
	// ѕеремещаем м€ч
	m_Shape.setPosition(m_Position);
}
void Ball::ballspeed()
{
	if (m_Speed < 3000) {
		m_Speed += 200;
	}
	else
	{

		m_Speed = 2990;
	}
}
void Ball::ballSpeedDefault() {
	m_Speed = 600.0f; 
}
;