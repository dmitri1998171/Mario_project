#include "hero.hpp"

void HUD(String hud_string, int size, float x_pos, float y_pos, float x_Orig, float y_Orig){
    text.setString(hud_string);//задает строку тексту
    text.setPosition(x_pos, y_pos);//задаем позицию текста, центр камеры
    text.setOrigin(x_Orig, y_Orig);
    text.setCharacterSize(size);
}

void hud_game_Func(){
	ostringstream hud_scores;
	hud_scores << scores;
	ostringstream hud_health;
	hud_health << health;
	ostringstream hud_time;
	hud_time << playtime;

	HUD("Scores: "+hud_scores.str()+"\t\t\t  Lifes: "+hud_health.str()+"\t\t\t\tTime: "+hud_time.str(),12,10,10,0,0);
}