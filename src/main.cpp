#include "headers/menu.hpp"

/*
	В данный файл подключается только menu.hpp так как все остальные 
	заголовочные файлы подключены друг к другу конвеером(последовательно)
*/ 

void load_Resouces(){
// Загрузка шрифта
	font.loadFromFile("font/SourceCodePro-Regular.ttf");

// Загрузка изображений
	tileset.loadFromFile("Images/Mario_Luigi_tileset.png");
	s_map.setTexture(tileset);

	bg_tex.loadFromFile("Images/background.png");
	
// Загрузка аудио
	buffer.loadFromFile("Audio/Jump.ogg");
	sound.setVolume(10);

	music.openFromFile("Audio/Mario_Theme.ogg");
	music.setVolume(10);
	
	// Вкл. фоновую музыку
	music.play();
	music.setLoop(true);
}

int main(){
	load_Resouces();			// Загрузка ресурсов
		
	menu();						// Меню
	pause_Func();				// Пауза
	game_cycle();				// Игра
	hud_game_over_Func();		// Проиграл
	game_finished_Func();		// Выиграл
	return 0;
}
/*	игровые состояния:
game_state == 0 - меню
game_state == 1 - игра
game_state == 2 - пауза
game_state == 3 - проиграл
game_state == 4 - выйграл
*/ 

