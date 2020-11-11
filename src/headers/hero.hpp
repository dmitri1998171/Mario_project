#include "parameters.hpp"

/*
Tileset map:
size: 16x16

80x144 - Mario
80x163 - Luigi
*/ 

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
		sprite.setTextureRect(IntRect(80,163,16,16));
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
		for (int i=rect.top/16; i<(rect.top+rect.height)/16; i++){							// Проход по строкам кратным размеру 1 тайла
			for (int j=rect.left/16; j<(rect.left+rect.width)/16; j++){						// ... по столбцам ...
				if (TileMap[i][j] == 'P' || TileMap[i][j] == '0' || TileMap[i][j] == 'R' || // Если объект столкновения == ...
					TileMap[i][j] == 'T' || TileMap[i][j] == 'k' || TileMap[i][j] == 'p' ||
					TileMap[i][j] == 'r' || TileMap[i][j] == 't' || TileMap[i][j] == 'c' ||
					TileMap[i][j] == 'K' || TileMap[i][j] == 'q' || TileMap[i][j] == 'z' 
					|| TileMap[i][j] == 'i'
					){
					if ((dx>0) && (dir == 0)){ 							// Если ГГ слева от объекта столкновения
						if(TileMap[i][j] == 'i'){ TileMap[i][j] = ' '; scores += 1; }
						else{ rect.left = j*16 - rect.width; }}
					
					if ((dx<0) && (dir == 0)){ 							// Если ГГ справа
						if(TileMap[i][j] == 'i'){ TileMap[i][j] = ' '; scores += 1; }
						else{ rect.left = j*16 + 16; }}						
					
					if ((dy>0) && (dir == 1)){ 							// Если ГГ сверху
						if(TileMap[i][j] == 'i'){ TileMap[i][j] = ' '; scores += 1; }
						else{ rect.top = i*16 - rect.height; dy=0; onGround = true; }}	
					
					if ((dy<0) && (dir == 1)){ 							// Если ГГ снизу
						// Обработка [?]
						if (TileMap[i][j] == 'c'){
							TileMap[i][j] = ' '; 		// Убираем [?] с карты
							sprite.setScale(2,2);		// Маштабируем ГГ в х2
							sprite.setOrigin(8,8);		// устанавливаем геом. центр ГГ
							mode = true;				// вкл. модификатор
						}
						// Обработка кирпич. блока (красный и синий)
						else if(TileMap[i][j] == 'k' || TileMap[i][j] == 'K'){ TileMap[i][j] = ' '; } // Убираем блок с карты
						// Обработка монеток
						else if(TileMap[i][j] == 'i'){ TileMap[i][j] = ' '; scores += 1; }

						else{ rect.top = i*16 + 16; dy=0; }
					}
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
