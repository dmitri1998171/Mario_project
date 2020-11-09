#include "events.hpp"

// Объявляем классы героя, врагов
Player p(tileset);
Enemy enemy;

void camera_Func(){
// Управление камерой
	if(p.rect.left < 200){ offsetX = 0; }									// При загрузке уровня
	if(p.rect.left > 200){ offsetX = p.rect.left - 200; }					// Фикс. камеры в начале карты
}

void game_over_Func(){
	if(health == 0){ game_state = 3; }			// Кол-во оставшихся попыток
	if(p.rect.top > 260){ health -=1; p.rect.left = 16; p.rect.top = 208; }		// -1 жизнь если упал в яму
	if(game_timer == 0){ health -=1; p.rect.left = 16; p.rect.top = 208; }			// -1 жизнь если время вышло 
}

void choose_lvl_func(){
	if(lvl == 1){ 
		if(p.rect.left > 2180){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
		if(p.rect.left > 2233){ lvl += 0.5; p.rect.left = 16; }
		// printf("lvl 1\n");
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap1, sizeof(TileMap1));
		}
	if(lvl == 1.5){ 
		offsetX = 0;
		if(p.rect.left > 287){ if(p.rect.top > 207){ lvl += 0.5; p.rect.left = 16;	}}
		// printf("swap to lvl 1.5\n");
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap1_5, sizeof(TileMap1_5));
		}
	if(lvl == 2){
		if(p.rect.left > 2190){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
		if(p.rect.left > 2275){ lvl += 0.5; p.rect.left = 16; }
		// printf("swap to lvl 2\n");
		window.clear(Color(0,0,0));
		memcpy(TileMap, TileMap2, sizeof(TileMap2));
	}
	if(lvl == 2.5){
		offsetX = 0;
		if(p.rect.left > 383){ lvl += 0.5; p.rect.left = 296; p.rect.top = 208; }
		// printf("swap to lvl 2.5\n");
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap2_5, sizeof(TileMap2_5));
	}
	if(lvl == 3){
		offsetX = 0;
		if(scores == 44){ lvl += 0.5; }
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap3, sizeof(TileMap3));
	}
	if(lvl > 3){ game_state = 4; }
}

void boost_func(){
	if (p.mode){
		// printf("boost_time: %d\n", p.Timer1);
		p.Timer1 += myTime;
		if (p.Timer1>1500){
			p.mode = false;
		}
	}
	if(!p.mode){
		p.sprite.setScale(1,1);
		p.sprite.setOrigin(0,0);
		p.Timer1 = 0;
	}
}

void keyboard_Func(){
	if (Keyboard::isKeyPressed(Keyboard::Left)){ p.dx = -0.1; }					// Левая стрелка
	if (Keyboard::isKeyPressed(Keyboard::Right)){ p.dx = 0.1; }					// Правая стрелка
	if (Keyboard::isKeyPressed(Keyboard::Up)){ 									// Прыжок
		if (p.onGround){
			if(!p.mode){ p.dy = -0.5; p.onGround = false; }//sound.play(); } 
			if(p.mode){ p.dy = -0.7; p.dx +=0.1; p.onGround = false; }//sound.play(); }
		}
	}

	p.update(myTime);
	enemy.update(myTime);
}

void collision_with_enemy_Func(){
	if(p.rect.intersects(enemy.rect)){
		if(enemy.life){
			if(p.dy>0){ 							// Убил врага прыжком сверху
				enemy.dx=0; 		// останавливаем врага 
				p.dy=-0.2;  		// отпрыгиваем от врага 
				enemy.life = false; // убиваем
				scores += 10;		// получ. очки
			}
			else{ 									// Умер ГГ 
				if(p.mode){ p.mode = false; kill_boost = true;}			// если на бусте, то откл. буст
				if(!p.mode){											// если простой ГГ
					if(kill_boost){ 									// если только после буст
						kill_boost_timer += myTime;						// то отсчит. 2 сек. чтобы отойти от врага
						if (kill_boost_timer > 200){ kill_boost = false; }} // и откл. отсчет
					if(!kill_boost){									// если >2 сек. от буста или простой ГГ
						health -= 1;									// -1 жизнь
						p.rect.left = 16;								// уровень с начала
					}
				}	
			}
		}
	}
}

void draw_map_Func(){
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
}

void game_cycle(){
	Clock clock;
	
// если только начал играть(не продолжить)
	if(start_var){ lvl = 1; p.rect.left = 16; p.rect.top = 208; }
	
	while(game_state == 1){
	// music.play();
	// вывод индикаторов очков, жизней, времени на экран
		hud_game_Func();
		
	// Отсчет времени
		myTime = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		myTime = myTime/800;
		
	// Таймер оставшегося времени на уровень
		game_timer = 120;
		playtime += myTime / (2*1000);	// Время в секундах
		game_timer = game_timer - playtime;

		event_Func();					// Регистрация событий, управление камерой
		camera_Func();					// Управление камерой
		game_over_Func();				// Проверки на конец игры
		choose_lvl_func();				// Выбор уровня
		boost_func();					// Большой Марио - [?]
		keyboard_Func();				// Управление персонажем
		
		// view.setCenter(p.rect.left + 100, p.rect.top); 
		
		collision_with_enemy_Func();	// Проверка столкновения ГГ и врага
		draw_map_Func();				// ОТРИСОВКА КАРТЫ

		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.draw(text);
		window.display();
	}
}
