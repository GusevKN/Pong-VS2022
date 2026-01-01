#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
int main()
{
	// Создаем объект VideoMode
	VideoMode vm(1370, 760);
	// Создаем и открываем окно для игры в полноэкранном режиме
	RenderWindow window(vm, "Pong", Style::Fullscreen);
	int score = 0;
	int lives = 3;
	// Создаем ракетку в нижней центральной части экрана
	Bat bat(1370 / 2, 760 - 20);
	// Создаем мяч
	Ball ball(900 / 2, 0);
	// Мы добавим мяч в следующей главе
	// Создаем текстовый объект HUD
	Text hud;
	// Крутой ретрошрифт
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	// Устанавливаем шрифт
	hud.setFont(font);
	// Делаем его большим и красивым
	hud.setCharacterSize(75);
	// Выбираем цвет
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);
		// Таймер для управления временем
	Clock clock;
	while (window.isOpen())
	{
		/*
		Обработка ввода игрока
		**************************************
		**************************************
		**************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Выход из игры при закрытии окна
				window.close();
		}
		// Обработка выхода игрока
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		// Обработка нажатия и отпускания клавиш со стрелками
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}
		/*
		Обновление ракетки, мяча и HUD
		**************************************
		**************************************
		**************************************
		*/
		// Обновление delta time
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		// Обновление текста HUD
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());
		// Обработка столкновения мяча с нижней границей экрана
		if (ball.getPosition().top > window.getSize().y)
		{
			// Смена направления движения мяча
			ball.reboundBottom();
			// Уменьшение количества жизней
			lives--;
			// Проверка оставшегося количества жизней
			if (lives < 1) {
				// Сброс счета
				score = 0;
				// Сброс жизней
				lives = 3;
			}
			
		}
		// Обработка столкновения мяча с верхней границей экрана
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			// Добавление одного очка к счету игрока
			score++;
		}
		// Обработка столкновения мяча с боковыми границами экрана
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + ball.getPosition().width> window.getSize().x)
		{
			ball.reboundSides();
		}
		// Мяч столкнулся с ракеткой?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			// Обнаружение столкновения, изменение направления движения мяча
			// и добавление одного очка к счету
			ball.reboundBatOrTop();
		}
		/*
		Отрисовка ракетки, мяча и HUD
		**************************************
		**************************************
		**************************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}
	return 0;
}