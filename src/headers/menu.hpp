#include "game_cycle.hpp"

int menu_state = 0;

void menu_mouse_Click_Func();
void multiplayer_mouse_Click_Func();
void menu();

void multiplayer_munu_Func(){
    if(menu_state == 1){
        bg_tex.loadFromFile("Images/background.png");
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
        host_text.setFillColor(sf::Color::White);
        host_text.setStyle(sf::Text::Bold);

        Text client_text("I'm Client", font, 24);
        client_text.setPosition(W_window/2, H_window/2+65);
        client_text.setOrigin(W_window/4.5, W_window/20);
        client_text.setFillColor(sf::Color::White);
        client_text.setStyle(sf::Text::Bold);

        Text back("Back", font, 24);
        back.setPosition(W_window/2, H_window/2+105);
        back.setOrigin(W_window/12, W_window/20);
        back.setFillColor(sf::Color::White);
        back.setStyle(sf::Text::Bold);

        while(1){
            event_Func();
            multiplayer_mouse_Click_Func();

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

void menu(){
    if(game_state == 0){   
        if(menu_state == 0){
            bg_tex.loadFromFile("Images/background.png");
            bg_sprite.setTexture(bg_tex);
            bg_sprite.setScale(1.25, 1.6);

            RectangleShape play_game_button(Vector2f(W_window/3+10, H_window/10));
            play_game_button.setFillColor(Color(0,255,0, 200));
            play_game_button.setPosition(W_window/3-10, H_window/2+5);
            play_game_button.setOrigin(0.5, 0);

            RectangleShape multiplayer_button(Vector2f(W_window/3+40, H_window/10));
            multiplayer_button.setFillColor(Color(255,255,0, 200));
            multiplayer_button.setPosition(W_window/3-25, H_window/2+50);
            multiplayer_button.setOrigin(0.5, 0);

            RectangleShape quit_button(Vector2f(W_window/5, H_window/10));
            quit_button.setFillColor(Color(255,0,0, 200));
            quit_button.setPosition(W_window/2, H_window/2+107);
            quit_button.setOrigin(W_window/10, W_window/20);

// ----------------------------------------------------------------------

            Text play_game("Play game", font, 24);
            play_game.setPosition(W_window/2, H_window/2+20);
            play_game.setOrigin(W_window/5.5, W_window/20);
            play_game.setFillColor(sf::Color::White);
            play_game.setStyle(sf::Text::Bold);

            Text multiplayer_text("Multiplayer", font, 24);
            multiplayer_text.setPosition(W_window/2, H_window/2+65);
            multiplayer_text.setOrigin(W_window/4.5, W_window/20);
            multiplayer_text.setFillColor(sf::Color::White);
            multiplayer_text.setStyle(sf::Text::Bold);

            Text quit("Quit", font, 24);
            quit.setPosition(W_window/2, H_window/2+105);
            quit.setOrigin(W_window/12, W_window/20);
            quit.setFillColor(sf::Color::White);
            quit.setStyle(sf::Text::Bold);

            while(1){
                event_Func();
                menu_mouse_Click_Func();

                window.clear();
                window.draw(bg_sprite);

                window.draw(play_game_button);
                window.draw(multiplayer_button);
                window.draw(quit_button);
                
                window.draw(multiplayer_text);
                window.draw(play_game);
                window.draw(quit);
                
                window.display();
            }
        }
        if(menu_state == 1){ multiplayer_munu_Func(); }
    }
}

void multiplayer_mouse_Click_Func(){
    Vector2i mousePosition = Mouse::getPosition(window);
    printf("\tX: %i\tY: %i\n", mousePosition.x, mousePosition.y);
    
    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 123 && mousePosition.x < 265){
            if(mousePosition.y > 133 && mousePosition.y < 156){
                printf("play game\n");
                game_state = 1;
                game_cycle();
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 108 && mousePosition.x < 280){
            if(mousePosition.y > 175 && mousePosition.y < 200){
                printf("Multiplayer\n");
                menu_state = 1;
                multiplayer_munu_Func();
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 160 && mousePosition.x < 240){
            if(mousePosition.y > 213 && mousePosition.y < 237){
                printf("Back\n"); menu_state = 0; menu(); }
        }
    }
}

void menu_mouse_Click_Func(){
    Vector2i mousePosition = Mouse::getPosition(window);
    printf("\tX: %i\tY: %i\n", mousePosition.x, mousePosition.y);
    
    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 123 && mousePosition.x < 265){
            if(mousePosition.y > 133 && mousePosition.y < 156){
                printf("play game\n");
                game_state = 1;
                game_cycle();
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 108 && mousePosition.x < 280){
            if(mousePosition.y > 175 && mousePosition.y < 200){
                printf("Multiplayer\n");
                menu_state = 1;
                multiplayer_munu_Func();
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Left)){
        if(mousePosition.x > 160 && mousePosition.x < 240){
            if(mousePosition.y > 213 && mousePosition.y < 237){
                printf("Quit\n"); exit(0); }
        }
    }
}

void pause_Func(){
    if(game_state == 2){


        while(1){
            event_Func();

            window.clear();
            window.draw(bg_sprite);
            // window.draw(play_game_button);
            // window.draw(quit_button);
            window.draw(text);
            window.display();
        }
    }
}

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
        play_again.setFillColor(sf::Color::White);
        play_again.setStyle(sf::Text::Bold | sf::Text::Underlined);

        Text quit_button("Quit", font, 24);
        quit_button.setPosition(W_window/2, H_window/2+65);
        quit_button.setOrigin(W_window/12, W_window/20);
        quit_button.setFillColor(sf::Color::White);
        quit_button.setStyle(sf::Text::Bold | sf::Text::Underlined);


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
        play_again.setFillColor(sf::Color::White);
        play_again.setStyle(sf::Text::Bold | sf::Text::Underlined);

        Text quit_button("Quit", font, 24);
        quit_button.setPosition(W_window/2, H_window/2+65);
        quit_button.setOrigin(W_window/12, W_window/20);
        quit_button.setFillColor(sf::Color::White);
        quit_button.setStyle(sf::Text::Bold | sf::Text::Underlined);


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