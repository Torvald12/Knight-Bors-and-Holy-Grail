#include "menu.h"

void menu(RenderWindow &window) 
{
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("111.png");
	menuTexture2.loadFromFile("222.png");
	menuTexture3.loadFromFile("333.png");
	aboutTexture.loadFromFile("about.png");
	menuBackground.loadFromFile("knight.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(50, 30);
	menu2.setPosition(50, 275);
	menu3.setPosition(50, 519);
	menuBg.setPosition(768, 0);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(255, 100, 100));
 
		if (IntRect(50, 30, 700, 245).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); menuNum = 1; }
		if (IntRect(50, 275, 700, 244).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); menuNum = 2; }
		if (IntRect(50, 519, 700, 244).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); menuNum = 3; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false; //если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
	////////////////////////////////////////////////////
}