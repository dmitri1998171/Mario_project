#include "hud.hpp"

void pause_Func();
void game_cycle();
void multiplayer_menu_Func();
void menu();
void client_move_draw();
void host_move_draw();

void host_script();
void client_script();

void host_keyboard_send_Func();
void host_keyboard_receive_Func();
void client_keyboard_send_Func();
void client_keyboard_receive_Func();


// ============================================================
// скрипт если нажатие было на кнопку play game в главном меню
// обнуляет переменные
void play_game_script(){ 
    printf("play game\n"); 
    game_state = 1; 
    start_var = true; 
    health = 3;
    scores = 0;
    playtime = 0;
    game_cycle(); }

void multiplayer_script(){ 
	printf("Multiplayer\n"); 
	menu_state = 1; 
	multiplayer_menu_Func(); 
}

// скрипт выхода из игры
// включает в себя проверку отправки команды на выход от клиента к хосту и обратно 
void quit_script(){ 
	printf("Quit\n");
	if(im_host==true){
		char client_quit_snd[255];
		sprintf(client_quit_snd, "%s", "QUIT");
		if(client.send(client_quit_snd, sizeof(client_quit_snd)) != sf::Socket::Done){
			cout<<"host quit send: error\n";}
		socket.disconnect();
	}
	else if(im_client==true){
		char client_quit_snd[255];
		sprintf(client_quit_snd, "%s", "QUIT");
		if(socket.send(client_quit_snd, sizeof(client_quit_snd)) != sf::Socket::Done){
			cout<<"client quit send: error\n";}
		client.disconnect();
	}
	
	exit(EXIT_SUCCESS); 
}

// --------------------------------------------
// ... кнопка continue в меню паузы
void continue_script(){ printf("Continue\n"); game_state = 1; game_cycle(); }
// ... кнопка Main menu в меню паузы
void menu_script(){ printf("Main menu\n"); game_state = 0; menu_state = 0; menu(); }
// ... кнопка back в меню паузы
void back_script(){ printf("Back\n"); menu_state = 0; menu(); }
// ============================================================

// Униферсальная функция для определения рабочей зоны кнопок в меню
// получает функции как аргументы и вызывает их в зависимости от координат курсора в момент нажатия на ЛКМ
void Click_Func(void(*first_script)(), void(*second_script)(), void(*third_script)()){
	Vector2i mousePosition = Mouse::getPosition(window);
	
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

// Обработка событий, постоянно ведет опрос соответствующих объектов(Mouse, Keyboard) на наличие изменений
void event_Func(){
	while(window.pollEvent(event)){
		if(event.type == Event::Closed) { exit(0); }  
		
    // Нажатия левой кнопки мыши в меню
		if(event.type == Event::MouseButtonReleased &&
        	event.mouseButton.button == Mouse::Left){
			if(game_state == 0 ){       // Если меню
        if(menu_state == 0){      // ... Главное меню
          Click_Func(play_game_script, multiplayer_script, quit_script); }
        if(menu_state == 1){      // ... multiplayer меню
          Click_Func(host_script, client_script, back_script); }
        if(menu_state == 2){      // ... меню паузы
          Click_Func(continue_script,menu_script,quit_script); }
			}
      if(game_state == 3){        // Если проиграл
        Click_Func(play_game_script, quit_script, quit_script); }
      if(game_state == 4){        // Если выиграл
        Click_Func(play_game_script, quit_script, quit_script); }
        }
	
    // ... кнопка Escape
    // В зависимости от того, где была нажата кнопка, действие будет разным
		if(event.type == Event::KeyReleased &&
        event.key.code == Keyboard::Escape){
			if(game_state == 1){                        // Пауза
				printf("Pause\n");
				game_state = 0; 
				menu_state = 2; 
				pause_Func(); }		
			if(game_state == 0 ||                       // меню, проиграл, выиграл
         game_state == 3 || 
         game_state == 4){
          if(menu_state == 2){ game_state = 1; start_var = false; game_cycle(); } // Продолжить
          else exit(0); }         				        // Выход из игры		
		}


    // изменение размера окна
    // shortcut ctrl+F
    if(Keyboard::isKeyPressed(Keyboard::LControl)){
      if(event.type == Event::KeyReleased &&
        event.key.code == Keyboard::F){
        
        // получаем размеры монитора 
        W_desktop = VideoMode::getDesktopMode().width;
        H_desktop = VideoMode::getDesktopMode().height;

        // 1-ое нажатие ctrl+F - размеры окна 640х480
        if(win_size_check == 1){ window.setSize(Vector2u(640, 480)); }
        // 2-ое нажатие ctrl+F - размеры окна = размерам монитора
        if(win_size_check == 2){ window.setSize(Vector2u(W_desktop, H_desktop)); }
        // 3-ое нажатие ctrl+F - размеры окна обнуляются до стандартных
        if(win_size_check == 3){ win_size_check = 0; window.setSize(Vector2u(W_window, H_window));}
        window.display();
        win_size_check++;
      }
    }
	}
}
