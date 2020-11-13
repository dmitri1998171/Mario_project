#include "network.hpp"

void hud_game_over_Func();
void game_finished_Func();
// // Объявляем классы героя, врагов
// Player p(tileset);
// Enemy enemy[5];

void camera_Func(Player* _p){
// Управление камерой
	if(_p->rect.left < 200){ offsetX = 0; }									// При загрузке уровня
	if(_p->rect.left > 200){ offsetX = _p->rect.left - 200; }					// Фикс. камеры в начале карты
}

void game_over_Func(Player* _p){
	if(health == 0){ game_state = 3; hud_game_over_Func(); }					// Кол-во оставшихся попыток
	if(_p->rect.top > 250){ health -=1; _p->rect.left = 16; _p->rect.top = 208; }		// -1 жизнь если упал в яму
	if(game_timer == 0){ health -=1; _p->rect.left = 16; _p->rect.top = 208; }		// -1 жизнь если время вышло 
}

void collision_with_enemy_Func(int k, Player* _p){
	if(_p->rect.intersects(enemy[k].rect)){
		if(enemy[k].life){
			if(_p->dy>0){ 							// Убил врага прыжком сверху
				enemy[k].dx=0; 		// останавливаем врага 
				_p->dy=-0.2;  		// отпрыгиваем от врага 
				enemy[k].life = false; // убиваем
				scores += 10;		// получ. очки
			}
			else{ 									// Умер ГГ 
				if(_p->mode){ _p->mode = false; kill_boost = true; }		// если на бусте, то откл. буст
				if(!_p->mode){											// если простой ГГ
					if(kill_boost){ 									// если только после буст
						kill_boost_timer += myTime;						// то отсчит. 2 сек. чтобы отойти от врага
						if (kill_boost_timer > 200){ kill_boost = false; }
					} // и откл. отсчет
					if(!kill_boost){									// если >2 сек. от буста или простой ГГ
						health -= 1;									// -1 жизнь
						_p->rect.left = 16;								// уровень с начала
					}
				}
			}
		}
	}
}
void choose_lvl_func(Player* _p){
	if(lvl == 1){ 
		if(_p->rect.left > 2180){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
		if(_p->rect.left > 2233){ lvl += 0.5; _p->rect.left = 16; }

		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap1, sizeof(TileMap1));
	}
	if(lvl == 1.5){ 
		offsetX = 0;

		if(_p->rect.left > 287){ 
			if(_p->rect.top > 207){ 
				lvl += 0.5;
				_p->rect.left = 16;
				for(int i=0; i<5; i++){ enemy[i].life = true; }
			}
		}

		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap1_5, sizeof(TileMap1_5));
	}
	if(lvl == 2){
		if(_p->rect.left > 2190){ offsetX = W_window+1800 - 200; }			// Фикс. камеры в конце
		if(_p->rect.left > 2275){ lvl += 0.5; _p->rect.left = 16; }
		window.clear(Color(0,0,0));
		memcpy(TileMap, TileMap2, sizeof(TileMap2));
	}
	if(lvl == 2.5){
		offsetX = 0;
		local_scores = scores;
		if(_p->rect.left > 383){ 
			lvl += 0.5; 
			_p->rect.left = 296;
			_p->rect.top = 208;
		}
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap2_5, sizeof(TileMap2_5));
	}
	if(lvl == 3){
		srand(time(0));
		offsetX = 0;
		if(scores == local_scores+100){ lvl += 0.5; }
		window.clear(Color(107,140,255));
		memcpy(TileMap, TileMap3, sizeof(TileMap3));
		local_timer = 0;
		for(int i=1; i<H-1; i++){
			for(int j=1; j<26-1; j++){
				if(local_timer == 200){
					local_timer = 0;
					if(TileMap[i][j] == ' '){
						gen_trigger = 0 + rand() % 2;
						if(gen_trigger == 1){ TileMap[i][j] = 'i'; }
					}
				}
				local_timer += myTime;
			}
		}
	}
	if(lvl > 3){ game_state = 4; game_finished_Func(); }
}

void boost_func(Player* _p){
	if (_p->mode){
		// printf("boost_time: %d\n", p.Timer1);
		_p->Timer1 += myTime;
		if (_p->Timer1>1500){
			_p->mode = false;
		}
	}
	if(!_p->mode){
		_p->sprite.setScale(1,1);
		_p->sprite.setOrigin(0,0);
		_p->Timer1 = 0;
	}
} 

void keyboard_Func(Player* _p){
	char client_snd_data[255];
	bool trigger = false;
	
	if (Keyboard::isKeyPressed(Keyboard::Left)){ 
		_p->dx = -0.1; 
		trigger = true;
		if(im_client==true && trigger == true){
			memset(client_snd_data, 0, sizeof(client_snd_data));
			sprintf(client_snd_data, "%s", "LEFT");
			if(socket.send(client_snd_data, sizeof(client_snd_data)) != sf::Socket::Done)
			{cout<<"client keyboard send: error\n";}
			//else
				//cout<<"client keyboard send: success\n";
			trigger=false;
		}
	}					// Левая стрелка
	
	if (Keyboard::isKeyPressed(Keyboard::Right)){ 
		_p->dx = 0.1; 
		trigger=true;
		if(im_client==true && trigger==true){
			memset(client_snd_data, 0, sizeof(client_snd_data));
			sprintf(client_snd_data, "%s", "RIGHT");
			if(socket.send(client_snd_data, sizeof(client_snd_data)) != sf::Socket::Done)
			{cout<<"client keyboard send: error\n";}
			//else
				//cout<<"client keyboard send: success\n";
			trigger==false;
		}
	}// Правая стрелка
	
	if (Keyboard::isKeyPressed(Keyboard::Up)){														// Прыжок
		if (_p->onGround){
			if(!_p->mode){ _p->dy = -0.5; _p->onGround = false; }//sound.play(); } 
			if(_p->mode){ _p->dy = -0.7; _p->dx +=0.1; _p->onGround = false; }//sound.play(); }
		}
	}

	
}

void draw_map_Func(){
	for (int i=0; i<H; i++){
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
}

void network_client_Func()
{
	//Что нужно передавать клиаенту:
	//	1) То, что была нажата какая-либо клавиша
	//	2) То, что был произведен выход из игры(мультиплеера)
	//Что нужно принимать клиенту (отдельным потоком):
	//	1) Просчитанные сервером коордиаты его персонажа
	//	2) Прочитанные сервером координаты персонажа хоста
	//	3) Выход хоста из игры => конец игры(в мультиплеере) и у клиента
	
	
			//p.rect.left	Это Х координата
			//p.rect.top	Это Y координата
			//Разработать механизм по которому удаленный клиент перемещается по карте
			//keyboard_func
			//А лучше даже передавать p.dx и p.dy Комп сам все расчитает
			//
			//опеределиться (после start_var) с классами для отрисовки персонажей
		
	
	//Дописать то, что прописано в ивенте
}
void network_host_Func()
{
}

void game_cycle(){
	Clock clock;
	
// если только начал играть(не продолжить)
	if(start_var){ lvl = 1; p.rect.left = 16; p.rect.top = 208; }
	
// координаты врагов 
	// lvl1
	enemy[0].set(tileset,48*16,208);
	enemy[1].set(tileset,48*24,208); 
	enemy[2].set(tileset,48*30,208); 
	// lvl2 
	enemy[3].set(tileset,48*12,208); 
	enemy[4].set(tileset,48*19,208); 

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

		// camera_Func();					// Управление камерой
		// game_over_Func();				// Проверки на конец игры
		// choose_lvl_func();				// Выбор уровня
		// boost_func();					// Большой Марио - [?]
		// keyboard_Func();				// Управление персонажем

		if((im_host==true) || (im_host==false && im_client==false))
			camera_Func(&p);					// Управление камерой
		else if(im_client==true && im_host==false)
			camera_Func(&l);
		
		if(im_host==true || (im_host==false && im_client==false)){
			game_over_Func(&p);				// Проверки на конец игры
		}
		else if(im_host==false && im_client==true){
			game_over_Func(&l);
		}

		if(im_host==true || (im_host==false && im_client==false))
			choose_lvl_func(&p);				// Выбор уровня
		else
			choose_lvl_func(&l);
		
		if(im_host==true || (im_host==false && im_client==false))
			boost_func(&p);						// Большой Марио - [?]
		else if(im_host==true || im_client==true)
			boost_func(&l);

		if(window.hasFocus() && ((im_host==true) || (im_host==false && im_client==false)))
			keyboard_Func(&p);				// Управление персонажем
		else if(window.hasFocus() && (im_client==true)){
			keyboard_Func(&l);
		}
		draw_map_Func();				// ОТРИСОВКА КАРТЫ
		
		if(im_host==false && im_client==false)
			window.draw(p.sprite);
		else if(im_host==true || im_client==true){
			window.draw(p.sprite);
			window.draw(l.sprite);
		}

		for(int i=0; i<5;i++){
			enemy[i].update(myTime);
			window.draw(enemy[i].sprite);
			if(im_host==false && im_client==false)
				collision_with_enemy_Func(i, &p);	// Проверка столкновения ГГ и врага
			else if(im_host==true || im_client==true){
				collision_with_enemy_Func(i, &p);
				collision_with_enemy_Func(i, &l);
			}
		}
	
		if(im_host==false && im_client==false)
			p.update(myTime, true);
		else if(im_host==true || im_client==true){
			l.update(myTime, false);
			p.update(myTime, true);
		}
		//p.update(myTime);
		window.draw(p.sprite);
		window.draw(l.sprite);
		window.draw(text);
		window.display();
	}
}
