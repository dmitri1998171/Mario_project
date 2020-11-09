#include "maps.hpp"

int W_window = 400, H_window = 250;     // Размеры окна
int game_state = 0, scores = 0, health = 3; 
float myTime;
int playtime = 0;
int menu_state = 0;
bool start_var = true;

Texture tileset, bg_tex;
Sprite s_map, bg_sprite, menu_image;
Font font;
Text text("", font, 20);
Event event;
View view;
SoundBuffer buffer;
Music music;

RenderWindow window(VideoMode(W_window, H_window),"Mario_project");