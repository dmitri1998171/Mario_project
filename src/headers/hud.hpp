#include "hero.hpp"

// Функция получает строку, размер букв, ортоготальную позицию
// на экране, позицию осей и выводит это на экран
void HUD(String hud_string, int size, float x_pos, float y_pos, float x_Orig, float y_Orig){
    text.setString(hud_string);				// Задает строку тексту
    text.setFillColor(Color::White);		// Цвет
	text.setPosition(x_pos, y_pos);			// Позиция текста, центр камеры
    text.setOrigin(x_Orig, y_Orig);			// Геометрический центр текста
    text.setCharacterSize(size);			// Размер букв
}

// Функция приводит стандартные типы данных к необходимым 
// для корректного вывода на экран 
void hud_game_Func(){
	ostringstream hud_scores;
	hud_scores << scores;
	ostringstream hud_health;
	hud_health << health;
	ostringstream hud_time;
	hud_time << game_timer;

	HUD("Scores: "+hud_scores.str()+"\t\t\t  Lifes: "+hud_health.str()+"\t\t\t  Time: "+hud_time.str(),12,10,10,0,0);
}