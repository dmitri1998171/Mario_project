#include "hud.hpp"

void pause_Func();
void game_cycle();
void multiplayer_menu_Func();
void menu();

// --------------------------------------------

void play_game_script(){ 
    printf("play game\n"); 
    game_state = 1; 
    start_var = true; 
    health = 3;
    scores = 0;
    playtime = 0;
    game_cycle(); }

void multiplayer_script(){ printf("Multiplayer\n"); menu_state = 1; multiplayer_menu_Func(); }
void quit_script(){ printf("Quit\n"); exit(0); }

void host_script(){  }
void client_script(){  }
void back_script(){ printf("Back\n"); menu_state = 0; menu(); }

void continue_script(){ printf("Continue\n"); game_state = 1; game_cycle(); }
void menu_script(){ printf("Main menu\n"); game_state = 0; menu_state = 0; menu(); }

// --------------------------------------------

void Click_Func(void(*first_script)(), void(*second_script)(), void(*third_script)()){
	Vector2i mousePosition = Mouse::getPosition(window);
	// printf("\tX: %i\tY: %i\n", mousePosition.x, mousePosition.y);
	
    if(mousePosition.x > 123 && mousePosition.x < 265){
        if(mousePosition.y > 133 && mousePosition.y < 156){
            { first_script(); }}}
        
    if(mousePosition.x > 108 && mousePosition.x < 280){
        if(mousePosition.y > 175 && mousePosition.y < 200){
            { second_script(); }}}

    if(mousePosition.x > 160 && mousePosition.x < 240){
        if(mousePosition.y > 213 && mousePosition.y < 237){
            { third_script(); }}}
    
}

void event_Func(){
// Обработка событий
	while (window.pollEvent(event)){
		if (event.type == Event::Closed) { exit(0); }  
		
		if (event.type == Event::MouseButtonReleased &&
        	event.mouseButton.button == Mouse::Left){
			if(game_state == 0 || game_state == 2){
				if(menu_state == 0){
					Click_Func(play_game_script, multiplayer_script, quit_script); }
				if(menu_state == 1){
					Click_Func(host_script, client_script, back_script); }
				if(menu_state == 2){
					Click_Func(continue_script,menu_script,quit_script); }
			}
            if(game_state == 3){ 
                Click_Func(play_game_script, quit_script, quit_script); }
            if(game_state == 3){ 
                Click_Func(play_game_script, quit_script, quit_script); }
        }
	
		if (event.type == Event::KeyReleased &&
        event.key.code == Keyboard::Escape){
			if(game_state == 1){                        // Пауза
				printf("Pause\n");
				game_state = 0; 
				menu_state = 2; 
				pause_Func(); }		
			if(game_state == 0 || 
               game_state == 3 || 
               game_state == 4){
                if(menu_state == 2){ game_state = 1; start_var = false; game_cycle(); } // Продолжить
                else exit(0); }         				// Выход из игры		
		}
	}
}
