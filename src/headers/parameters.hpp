#include "maps.hpp"

int W_window = 400, H_window = 250;     // Размеры окна
int game_state = 1, menu_state = 0;
int game_timer = 120, scores = 0, health = 3; 
float playtime = 0, myTime = 0, kill_boost_timer = 0;
bool start_var = false, kill_boost = false;

bool im_host=false, im_client=false;

Texture tileset, bg_tex;
Sprite s_map, bg_sprite, menu_image;
Font font;
Text text("", font, 20);
Event event;
View view;
SoundBuffer buffer;
Music music;

RenderWindow window(VideoMode(W_window, H_window),"Mario_project");
