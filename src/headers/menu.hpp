#include "game_cycle.hpp"

/*
menu_state:
    0 - main menu
    1 - multiplayer
    2 - pause
*/ 

void menu();
void multiplayer_menu_Func();

// ======================================================================

// Основное меню
void menu(){
    if(game_state == 0){   
        if(menu_state == 0){
            // Задаем фон. изображение
            bg_sprite.setTexture(bg_tex);
            bg_sprite.setScale(1.25, 1.6);

            // Создаем объект типа "прямоугольник" 
            RectangleShape play_game_button(Vector2f(W_window/3+10, H_window/10));
            play_game_button.setFillColor(Color(0,255,0, 200));         // Цвет
            play_game_button.setPosition(W_window/3-10, H_window/2+5);  // Позиция
            play_game_button.setOrigin(0.5, 0);                         // Положение осей

            RectangleShape multiplayer_button(Vector2f(W_window/3+40, H_window/10));
            multiplayer_button.setFillColor(Color(255,255,0, 200));
            multiplayer_button.setPosition(W_window/3-25, H_window/2+50);
            multiplayer_button.setOrigin(0.5, 0);

            RectangleShape quit_button(Vector2f(W_window/5, H_window/10));
            quit_button.setFillColor(Color(255,0,0, 200));
            quit_button.setPosition(W_window/2, H_window/2+107);
            quit_button.setOrigin(W_window/10, W_window/20);

// ----------------------------------------------------------------------

            // Создаем текст, font - шрифт, 24 - размер букв
            Text play_game("Play game", font, 24);
            play_game.setPosition(W_window/2, H_window/2+20);
            play_game.setOrigin(W_window/5.5, W_window/20);
            play_game.setFillColor(Color::White);
            play_game.setStyle(Text::Bold); // Модификаторы текста(жирный, курсив, подчеркнутый, перечеркнутый и тд)

            Text multiplayer_text("Multiplayer", font, 24);
            multiplayer_text.setPosition(W_window/2, H_window/2+65);
            multiplayer_text.setOrigin(W_window/4.5, W_window/20);
            multiplayer_text.setFillColor(Color::White);
            multiplayer_text.setStyle(Text::Bold);

            Text quit("Quit", font, 24);
            quit.setPosition(W_window/2, H_window/2+105);
            quit.setOrigin(W_window/12, W_window/20);
            quit.setFillColor(Color::White);
            quit.setStyle(Text::Bold);

            while(1){
                event_Func();   // Вызов обработчика событий

                window.clear(); // Очистка экрана
                window.draw(bg_sprite); // Рисуем фон. изображение

                // Отрисовываем кнопки
                window.draw(play_game_button);
                window.draw(multiplayer_button);
                window.draw(quit_button);
                
                // ... текст на кнопках
                window.draw(multiplayer_text);
                window.draw(play_game);
                window.draw(quit);
                
                // обновляем экран
                window.display();
            }
        }
        if(menu_state == 1){ multiplayer_menu_Func(); }
    }
}

// подменю multiplayer
void multiplayer_menu_Func(){
    if(menu_state == 1){
        bg_sprite.setTexture(bg_tex);
        bg_sprite.setScale(1.25, 1.6);

        RectangleShape host_button(Vector2f(W_window/3+10, H_window/10));
        host_button.setFillColor(Color(0,255,0, 200));              
        host_button.setPosition(W_window/3-10, H_window/2+5);       
        host_button.setOrigin(0.5, 0);                              

        RectangleShape client_button(Vector2f(W_window/3+40, H_window/10));
        client_button.setFillColor(Color(255,255,0, 200));
        client_button.setPosition(W_window/3-25, H_window/2+50);
        client_button.setOrigin(0.5, 0);

        RectangleShape back_button(Vector2f(W_window/5, H_window/10));
        back_button.setFillColor(Color(255,0,0, 200));
        back_button.setPosition(W_window/2, H_window/2+107);
        back_button.setOrigin(W_window/10, W_window/20);

    // --------------------------------------------------------

        Text host_text("I'm Host", font, 24);
        host_text.setPosition(W_window/2, H_window/2+20);
        host_text.setOrigin(W_window/5.5, W_window/20);
        host_text.setFillColor(Color::White);
        host_text.setStyle(Text::Bold);  

        Text client_text("I'm Client", font, 24);
        client_text.setPosition(W_window/2, H_window/2+65);
        client_text.setOrigin(W_window/4.5, W_window/20);
        client_text.setFillColor(Color::White);
        client_text.setStyle(Text::Bold);

        Text back("Back", font, 24);
        back.setPosition(W_window/2, H_window/2+105);
        back.setOrigin(W_window/12, W_window/20);
        back.setFillColor(Color::White);
        back.setStyle(Text::Bold);

        while(1){
            event_Func();               
            
            window.clear();             
            window.draw(bg_sprite);     
             
            window.draw(host_button);   
            window.draw(client_button);
            window.draw(back_button);
                          
            window.draw(host_text);
            window.draw(client_text);
            window.draw(back);
                             
            window.display();
        }
    }
}

// меню паузы
void pause_Func(){
    if(game_state == 0){
        if(menu_state == 2){
            RectangleShape bg(Vector2f(W_window, H_window));
            bg.setFillColor(Color(255,255,255, 100));

            menu_image.setTexture(tileset);
            menu_image.setTextureRect(IntRect(80,144,16,16));
            menu_image.setPosition(W_window/2-((16*3)/2), H_window/2-80);
            menu_image.setScale(3,3);

            RectangleShape continue_button(Vector2f(W_window/3+10, H_window/10));
            continue_button.setFillColor(Color(0,255,0, 200));
            continue_button.setPosition(W_window/3-10, H_window/2+5);
            continue_button.setOrigin(0.5, 0);

            RectangleShape main_menu_button(Vector2f(W_window/3+40, H_window/10));
            main_menu_button.setFillColor(Color(255,255,0, 200));
            main_menu_button.setPosition(W_window/3-25, H_window/2+50);
            main_menu_button.setOrigin(0.5, 0);

            RectangleShape quit_button(Vector2f(W_window/5, H_window/10));
            quit_button.setFillColor(Color(255,0,0, 200));
            quit_button.setPosition(W_window/2, H_window/2+107);
            quit_button.setOrigin(W_window/10, W_window/20);

// ----------------------------------------------------------------------

            Text continue_text("Continue", font, 24);
            continue_text.setPosition(W_window/2, H_window/2+20);
            continue_text.setOrigin(W_window/5.5, W_window/20);
            continue_text.setFillColor(Color::White);
            continue_text.setStyle(Text::Bold);

            Text main_menu_text("Main menu", font, 24);
            main_menu_text.setPosition(W_window/2+15, H_window/2+65);
            main_menu_text.setOrigin(W_window/4.5, W_window/20);
            main_menu_text.setFillColor(Color::White);
            main_menu_text.setStyle(Text::Bold);

            Text quit("Quit", font, 24);
            quit.setPosition(W_window/2, H_window/2+105);
            quit.setOrigin(W_window/12, W_window/20);
            quit.setFillColor(Color::White);
            quit.setStyle(Text::Bold);

            while(1){
                event_Func();

                window.clear();
                window.draw(bg);
                window.draw(menu_image);

                window.draw(continue_button);
                window.draw(main_menu_button);
                window.draw(quit_button);
                
                window.draw(continue_text);
                window.draw(main_menu_text);
                window.draw(quit);

                window.display();
            }
        }
    }
}

// ======================================================================

// меню проигрыша
void hud_game_over_Func(){
    if(game_state == 3){
        RectangleShape g_o_bg(Vector2f(W_window, H_window));
        g_o_bg.setFillColor(Color(0,0,0));

        HUD("Game over!", 40, W_window/2, H_window/6,
            W_window/3.5, 0);
        text.setFillColor(Color::Red);

        Text play_again("Play again", font, 24);
        play_again.setPosition(W_window/2, H_window/2+20);
        play_again.setOrigin(W_window/5.5, W_window/20);
        play_again.setFillColor(Color::White);
        play_again.setStyle(Text::Bold | Text::Underlined);

        Text quit_button("Quit", font, 24);
        quit_button.setPosition(W_window/2, H_window/2+65);
        quit_button.setOrigin(W_window/12, W_window/20);
        quit_button.setFillColor(Color::White);
        quit_button.setStyle(Text::Bold | Text::Underlined);


        while(1){
            event_Func();

            window.clear();
            window.draw(g_o_bg);
            window.draw(text);
            window.draw(play_again);
            window.draw(quit_button);
            window.display();
        }
    }
}

// меню выигрыша
void game_finished_Func(){
    if(game_state == 4){
        RectangleShape g_c_bg(Vector2f(W_window, H_window));
        g_c_bg.setFillColor(Color(107,140,255));

        HUD("!!!Congratulations!!!\n\tGame completed", 30, W_window/2, H_window/6,
            W_window/2.15, 0);
        text.setFillColor(Color::Green);

        Text play_again("Play again", font, 24);
        play_again.setPosition(W_window/2, H_window/2+20);
        play_again.setOrigin(W_window/5.5, W_window/20);
        play_again.setFillColor(Color::White);
        play_again.setStyle(Text::Bold | Text::Underlined);

        Text quit_button("Quit", font, 24);
        quit_button.setPosition(W_window/2, H_window/2+65);
        quit_button.setOrigin(W_window/12, W_window/20);
        quit_button.setFillColor(Color::White);
        quit_button.setStyle(Text::Bold | Text::Underlined);


        while(1){
            event_Func();

            window.draw(g_c_bg);
            window.draw(text);
            window.draw(play_again);
            window.draw(quit_button);
            window.display();
        }
    }
}