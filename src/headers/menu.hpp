#include "game_cycle.hpp"

void menu(){
    if(game_state == 0){   
        bg_tex.loadFromFile("Images/background.png");
        bg_sprite.setTexture(bg_tex);
        bg_sprite.setScale(1.25, 1.6);

        RectangleShape play_game_button(Vector2f(W_window/5, H_window/10));
        play_game_button.setFillColor(Color(0,255,0));
        play_game_button.setPosition(W_window/2, H_window/2+30);
        play_game_button.setOrigin(W_window/10, W_window/20);

        RectangleShape quit_button(Vector2f(W_window/5, H_window/10));
        quit_button.setFillColor(Color(255,0,0));
        quit_button.setPosition(W_window/2, H_window/2+65);
        quit_button.setOrigin(W_window/10, W_window/20);

        // HUD("Play game", 20, W_window/2, H_window/2+30,
        //     W_window/7, W_window/20);
        // text.setFillColor(Color::Red);
        // text.setStyle(Text::Bold | Text::Underlined);//жирный и подчеркнутый текст

        Text play_game("Play game", font, 24);
        play_game.setPosition(W_window/2, H_window/2+20);
        play_game.setOrigin(W_window/5.5, W_window/20);
        play_game.setFillColor(sf::Color::White);
        play_game.setStyle(sf::Text::Bold | sf::Text::Underlined);

        Text quit("Quit", font, 24);
        quit.setPosition(W_window/2, H_window/2+65);
        quit.setOrigin(W_window/12, W_window/20);
        quit.setFillColor(sf::Color::White);
        quit.setStyle(sf::Text::Bold | sf::Text::Underlined);


        while(1){
            event_Func();

            window.clear();
            window.draw(bg_sprite);
            // window.draw(play_game_button);
            // window.draw(quit_button);
            window.draw(text);
            window.draw(play_game);
            window.draw(quit);
            window.display();
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