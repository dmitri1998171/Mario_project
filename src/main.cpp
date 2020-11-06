#include "header.hpp"
#include <stdlib.h>
#include <string.h>

int W_window = 400, H_window = 250;
int scores = 0, playtime = 0;
bool life = true, check_win = false;

class Player{
	public:
		int Timer1,Timer2;
		float dx,dy;
		FloatRect rect;
		bool onGround, mode;
		Sprite sprite;
		float CurrentFrame;

	Player(Texture & image){
		Timer2 = 0;
		Timer1 = 0;
		mode = false;
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(80,144,16,16));
		rect = FloatRect(52,32,16,16);

		dx=dy=0;
		CurrentFrame = 0;
	}

	void update(float time){
		rect.left += dx * time;		// Движение по формуле: "скорость, время, растояние"
		Collision(0);				// Вызов функции рассчета столкновений

	// Механика прыжка по параболе
		if (!onGround){ dy = dy + 0.0015*time; }
		rect.top += dy * time;
		onGround = false;
		Collision(1);

	// Анимация - смена тайлов
		CurrentFrame += 0.005*time; 
		if (CurrentFrame > 3){ CurrentFrame -=3; }
		if (dx<0){ sprite.setTextureRect(IntRect(80+31*int(CurrentFrame)+16,144,-16,16)); }
		if (dx>0){ sprite.setTextureRect(IntRect(80+31*int(CurrentFrame),144,16,16)); }
		
		sprite.setPosition(rect.left - offsetX,rect.top - offsetY);
		dx=0;
	}

	void Collision(int dir){
		for (int i=rect.top/16; i<(rect.top+rect.height)/16; i++)							// Проход по строкам кратным размеру 1 тайла
			for (int j=rect.left/16; j<(rect.left+rect.width)/16; j++){						// ... по столбцам ...
				if (TileMap[i][j] == 'P' || TileMap[i][j] == '0' || TileMap[i][j] == 'R' || // Если объект столкновения == ...
					TileMap[i][j] == 'T' || TileMap[i][j] == 'k' || TileMap[i][j] == 'p' ||
					TileMap[i][j] == 'r' || TileMap[i][j] == 't' || TileMap[i][j] == 'c' ||
					TileMap[i][j] == 'K' || TileMap[i][j] == 'q' || TileMap[i][j] == 'z'){
					if ((dx>0) && (dir == 0)){ rect.left = j*16 - rect.width; }				// Если ГГ слева от объекта столкновения
					if ((dx<0) && (dir == 0)){ rect.left = j*16 + 16; }						// Если ГГ справа
					if ((dy>0) && (dir == 1)){ rect.top = i*16 - rect.height; dy=0; onGround = true; }	// Если ГГ сверху
					if ((dy<0) && (dir == 1)){ 												// Если ГГ снизу
						// Обработка [?]
						if (TileMap[i][j] == 'c'){
							TileMap[i][j] = ' '; 		// Убираем [?] с карты
							sprite.setScale(2,2);		// Маштабируем ГГ в х2
							sprite.setOrigin(8,8);		// устанавливаем геом. центр ГГ
							mode = true;				// вкл. модификатор
						}
						if(TileMap[i][j] == 'k' || TileMap[i][j] == 'K'){ TileMap[i][j] = ' '; } // Убираем блок с карты
						
						rect.top = i*16 + 16; dy=0; 
						}
				}
			}
	}
};

class Enemy{
	public:
		float dx,dy;
		FloatRect rect;
		Sprite sprite;
		float CurrentFrame;
		bool life;

	void set(Texture &image, int x, int y){
		sprite.setTexture(image);
		rect = FloatRect(x,y,16,16);

		dx=0.05;
		CurrentFrame = 0;
		life = true;
	}

	void update(float time){
		rect.left += dx * time;
		Collision();

		CurrentFrame += time * 0.005;
		if (CurrentFrame>2){ CurrentFrame -= 2; }

		sprite.setTextureRect(IntRect(18*int (CurrentFrame),0,16,16));
		if (!life){ sprite.setTextureRect(IntRect(58,0,16,16)); }

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision(){
		for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
			for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++){
				if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0')){ 
					if (dx>0){ rect.left =  j*16 - rect.width; dx*=-1; }
					else if (dx<0){ rect.left =  j*16 + 16;  dx*=-1; }				
				}
			}
	}
};

int main(){
	RenderWindow window(VideoMode(W_window, H_window),"Mario_project");

	float CurrentFrame = 0;
	Clock clock;

// ====================== Загрузка ресурсов ======================
	Texture tileset;
	tileset.loadFromFile("Images/Mario_tileset.png");

	Sprite s_map;
	s_map.setTexture(tileset);

// Создаем классы героя, врагов
	Player p(tileset);
	Enemy enemy;
	enemy.set(tileset,48*16,208);

// ====================== Загрузка аудио ======================
	SoundBuffer buffer;
	buffer.loadFromFile("Audio/Jump.ogg");
	Sound sound(buffer);
	sound.setVolume(10);

	Music music;
	music.openFromFile("Audio/Mario_Theme.ogg");
	music.setVolume(10);

// ====================== Игровой цикл ======================
// обновление экрана, обработка событий, отрисовка карты

	while (window.isOpen()){
		// music.play();
	// Обработка событий
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) window.close(); }

	// Отсчет времени
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;

	// Управление камерой
		if(p.rect.left < 200){ offsetX = 0; }									// При загрузке уровня
		if(p.rect.left > 200){ offsetX = p.rect.left - 200; }					// Фикс. камеры в начале карты
	
	// Выбор уровня
		if(lvl == 1){ 
			if(p.rect.left > 2180){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
			if(p.rect.left > 2233){ lvl += 1; p.rect.left = 16;	}
			printf("lvl 1\n");
			window.clear(Color(107,140,255));
			memcpy(TileMap, TileMap1, sizeof(TileMap1));
		}
		if(lvl == 2){ 
			if(p.rect.left > 2190){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
			if(p.rect.left > 2275){ lvl += 1; p.rect.left = 16;	}
			printf("swap to lvl 2\n");
			window.clear(Color(0,0,0));
			memcpy(TileMap, TileMap2, sizeof(TileMap2));
		}
		if(lvl == 3){ 
			offsetX = 0;
			if(p.rect.left > 383){ lvl += 1; p.rect.left = 16;	}
			printf("swap to lvl 3\n");
			window.clear(Color(107,140,255));
			memcpy(TileMap, TileMap3, sizeof(TileMap3));
		}
		if(lvl > 3){ check_win = true; }

		printf("x: %f\ty: %f\n", p.rect.left, p.rect.top);
		
	// Большой Марио - [?]
		if (p.mode){
			p.Timer1 += time;
			if (p.Timer1>5000){
			p.sprite.setScale(1,1);
			p.sprite.setOrigin(0,0);
			p.Timer1 = 0;
			p.mode = false;
			}
		}

	// Управление персонажем
		if (Keyboard::isKeyPressed(Keyboard::Left)){ p.dx = -0.1; }					// Левая стрелка
		if (Keyboard::isKeyPressed(Keyboard::Right)){ p.dx = 0.1; }					// Правая стрелка
		if (Keyboard::isKeyPressed(Keyboard::Up)){ 									// Прыжок
			if (p.onGround){
				if (!p.mode){ p.dy = -0.5; p.onGround = false; }//sound.play(); } 
				if (p.mode){ p.dy = -0.7; p.dx +=0.1; p.onGround = false; }//sound.play(); }
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)){ window.close(); }			// Пауза

		p.update(time);
		enemy.update(time);

	// Проверка столкновения ГГ и врага
		if (p.rect.intersects(enemy.rect)){
			if (enemy.life){
				if (p.dy>0) { enemy.dx=0; p.dy=-0.2; enemy.life = false; }	// Убил врага прыжком сверху
				else { p.sprite.setColor(Color::Red); }						// Умер ГГ
			}
		}
		
// ====================== ОТРИСОВКА КАРТЫ ======================
		for (int i=0; i<H; i++)
			for (int j=0; j<W; j++){
				s_map.setColor(Color(255, 255, 255));
				s_map.setScale(1,1);
				if (TileMap[i][j]=='P'){ s_map.setTextureRect( IntRect(143-16*3,112,16,16) ); }			// Земля
				if (TileMap[i][j]=='p'){ s_map.setTextureRect( IntRect(143-16*3,112+16,16,16) ); }		// подземелье
				if (TileMap[i][j]=='i'){ s_map.setTextureRect( IntRect(0,17,14,20) ); }					// Монеты
				if (TileMap[i][j]=='k'){ s_map.setTextureRect( IntRect(143,112,16,16) ); }				// Красный кирпич
				if (TileMap[i][j]=='K'){ s_map.setTextureRect( IntRect(143,112+16,16,16) ); }			// Синий кирпич
				if (TileMap[i][j]=='c'){ s_map.setTextureRect( IntRect(143-16,112,16,16) ); }			// [?]
				if (TileMap[i][j]=='g'){ s_map.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) ); }		// Фон. гора зелени
				if (TileMap[i][j]=='d'){ s_map.setTextureRect( IntRect(0,106,74,127-106) ); }			// Куст
				if (TileMap[i][j]=='w'){ s_map.setTextureRect( IntRect(99,224,140-99,255-224) ); }		// Облако
				if (TileMap[i][j]=='r'){ s_map.setTextureRect( IntRect(143-32,112,16,16) ); }			// Красный блок
				if (TileMap[i][j]=='R'){ s_map.setTextureRect( IntRect(143-32,112+16,16,16) ); }		// Синий блок
				if (TileMap[i][j]=='U'){ s_map.setTextureRect( IntRect(96,4,107,105) ); }				// Замок
				if (TileMap[i][j]=='T'){ s_map.setTextureRect( IntRect(0,67,32,95-47) ); }				// | -обр. труба
				if (TileMap[i][j]=='t'){ s_map.setTextureRect( IntRect(0,47,32,95-47) ); }				// T -обр. труба
				if (TileMap[i][j]=='q'){ s_map.setTextureRect( IntRect(0,177,77,32) ); }				// -| обр. труба
				if (TileMap[i][j]=='m'){ 																// |- обр. труба
					s_map.setTextureRect( IntRect(0,177,77,32) );
					s_map.setScale(-1,1);
				}
				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')){ continue; }							// 0 - невидимый блок
				if (TileMap[i][j]=='1'){ 																// 1-ый блок
					s_map.setTextureRect(IntRect(143-32,112+16,16,16));
					s_map.setColor(Color(255, 0, 0)); }		
				if (TileMap[i][j]=='2'){ 																// 2-ой блок
					s_map.setTextureRect( IntRect(143-32,112+16,16,16));
					s_map.setColor(Color(0, 0, 255)); }		

				s_map.setPosition(j*16 - offsetX, i*16 - offsetY);
				window.draw(s_map);
			}
// =============================================================

		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
	return 0;
}
// TO DO
/*
	1) добавить карты
	2) падение в яму
	3) меню
	4) жизненный цикл
	\/ 5) коллизия со всеми видами 
	\/ 6) камера в конце карты
	\/ 7) Выбор уровня
	8) Правильная коллизия большого Марио
	9) HUD(жизни, время, очки)
	10) личные блоки (1,2)
	11) зациклить музыку
*/ 