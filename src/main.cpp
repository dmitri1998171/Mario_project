#include "headers/menu.hpp"

void load_Resouces(){
// Загрузка шрифта
	font.loadFromFile("font/SourceCodePro-Regular.ttf");

// Загрузка изображений
	tileset.loadFromFile("Images/Mario_tileset.png");
	s_map.setTexture(tileset);

	bg_tex.loadFromFile("Images/background.png");

	enemy.set(tileset,48*16,208);
	view.reset(FloatRect(0, 0, W_window, H_window));

// Загрузка аудио
	buffer.loadFromFile("Audio/Jump.ogg");
	Sound sound(buffer);
	sound.setVolume(10);

	music.openFromFile("Audio/Mario_Theme.ogg");
	music.setVolume(10);
}

int main(){
	load_Resouces();	// Загрузка ресурсов
	// printf("game_state: %i\n", game_state);
	// printf("x: %f\ty: %f\n", p.rect.left, p.rect.top);
	
	menu();						// Меню
	return 0;
}
/*	игровые состояния:
game_state == 0 - меню
game_state == 1 - игра
game_state == 2 - пауза
game_state == 3 - проиграл
game_state == 4 - выйграл
*/ 

// TO DO
/*
	8) Правильная коллизия большого Марио
	10) личные блоки (1,2)
	11) зациклить музыку
	12) пауза
*/ 