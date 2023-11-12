#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"

using namespace sf;

float offsetX=0, offsetY=0;

const int H=25;
const int W=41;

String TileMap[H]={
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B      AAAAA                            B",
"B     AA   AA   A    A                  B",
"B     AA       AAA  AAA               0 B",
"B     AA   AA   A    A        0 B   BBB B",
"B      AAAAA                 BBBB       B",
"B                               B       B",
"B              0                BBB     B",
"BBB            BB        B              B",
"B              BB       BB              B",
"B              BB      BBBB           BBB",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB          B",
"B                            BBBBB      B",
"B                               BBBB    B",
"B                               B       B",
"B                               B       B",
"B                             0 B       B",
"B        0          BBBB   BBBBBB       B",
"Bba     BBB                     B     0 B",
"BCc           BB                     BBBB",
"BDd           BB                        B",
"BBBB          BBBB       BB             B",
"B             BB         BB           0 B",
"B             BB         BB           B B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

class PLAYER
{
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	int counter;

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(1*32,1*32,60,87);

		dx = dy = 0.1;
		currentFrame = 0;
		counter = 0;
	}

	void update(float time)
	{
		rect.left+=dx*time;
		Collision(0);

		if(!onGround)
		{
			dy=dy+0.0005*time;
		}
		rect.top+=dy*time;
		onGround = false;

		Collision(1);

		currentFrame+=0.005*time;
		if(currentFrame>8)
		{
			currentFrame-=8;
		}
		if(dx<0)
		{
			sprite.setTextureRect(IntRect(60*int(currentFrame)+60,0,-60,87));
		}
		if(dx>0)
		{
			sprite.setTextureRect(IntRect(60*int(currentFrame),0,60,87));
		}

		sprite.setPosition(rect.left-offsetX, rect.top-offsetY);

		dx=0;

	}
	
	void Collision(int dir)
	{
		
		for(int i = rect.top/32; i<(rect.top+rect.height)/32; i++)
		{
			for(int j = rect.left/32; j<(rect.left+rect.width)/32; j++)
			{
				if (TileMap[i][j]=='B') 
				{
					if ((dx>0)&&(dir == 0)) rect.left = j*32 - rect.width;
					
					if ((dx<0)&&(dir == 0)) rect.left = j*32 +32;
					
					if ((dy>0)&&(dir == 1)) 
					{
						rect.top = i*32 - rect.height;
						dy=0;
						onGround = true;
					}
					
					if ((dy<0)&&(dir == 1)) 
					{
						rect.top = i*32 +32;
						dy=0;
					}
				}

				if (TileMap[i][j]=='0')
				{
					TileMap[i][j]=' ';
					counter++;
				}

				if (TileMap[i][j]=='D')
				{
					if(counter == 7)
					{
						counter = 0;
						Window WinWindow;
						WinWindow.create(VideoMode(300, 300), "You win!");
						while (WinWindow.isOpen())
						{
							Event event;
							while(WinWindow.pollEvent(event))
							{
								if(event.type == Event::Closed)
									WinWindow.close();
							}
						}
						WinWindow.display();
					}
				}
			}
		}

	}

};

int main()
{
	RenderWindow window(VideoMode(1300, 800), "Knight Bors and Holy Grail");
	menu(window);

	//Image icon;
	//if (!icon.loadFromFile("icon.png"))
	//{
		//EXIT_FAILURE;
	//}
	//window.setIcon(32, 32, icon.getPixelsPtr());

	Music music;
	if(!music.openFromFile("Audio.wav"))
	{
		std::cout << "ERROR";
	}
	music.play();
	music.setLoop(true);

	Texture t;
	t.loadFromFile("Paladin.png");
	
	Sprite tile(t);

	float currentFrame = 0;

	PLAYER p(t);

	Clock clock;

	//RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time=time/700;

		if (time>20)time =20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx=-0.1;

		}

		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx=0.1;
			
		}

		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			if(p.onGround)
			{
				p.dy=-0.35;
				p.onGround=false;
			}
		}

		p.update(time);

		if(p.rect.left>960)offsetX = p.rect.left - 960;
		if(p.rect.top>540) offsetY = p.rect.top - 540;

		window.clear(Color::White);

		for(int i=0; i<H; i++)
			for(int j=0; j<W; j++)
			{
				//if (TileMap[i][j]=='B') rectangle.setFillColor(Color::Black);
				//if (TileMap[i][j]=='0') rectangle.setFillColor(Color::Green);
				//if (TileMap[i][j]=='A') rectangle.setFillColor(Color::Red);
				//if (TileMap[i][j]=='D') rectangle.setFillColor(Color::Blue);
				//if (TileMap[i][j]=='C') rectangle.setFillColor(Color::Blue);
				//if (TileMap[i][j]==' ') continue;
				//==========================================================================
				if (TileMap[i][j]=='B') tile.setTextureRect(IntRect(65,88,97,120));
				if (TileMap[i][j]=='0') tile.setTextureRect(IntRect(0,88,31,120));
				if (TileMap[i][j]=='A') tile.setTextureRect(IntRect(32,88,64,120));

				if (TileMap[i][j]=='a') tile.setTextureRect(IntRect(130,88,162,120));
				if (TileMap[i][j]=='b') tile.setTextureRect(IntRect(98,88,129,120));

				if (TileMap[i][j]=='c') tile.setTextureRect(IntRect(130,120,162,152));
				if (TileMap[i][j]=='C') tile.setTextureRect(IntRect(98,120,129,152));

				if (TileMap[i][j]=='d') tile.setTextureRect(IntRect(130,152,162,184));
				if (TileMap[i][j]=='D') tile.setTextureRect(IntRect(98,152,129,184));

				if (TileMap[i][j]==' ') tile.setTextureRect(IntRect(180,122,212,154));
				//===========================================================================
				tile.setPosition(j*32-offsetX, i*32-offsetY);
				window.draw(tile);
			}
			window.draw(p.sprite);
			window.display();
	}

	return 0;
}