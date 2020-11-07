#include "header.hpp"

int W_window = 400, H_window = 250;
int scores = 0,  health = 3, playtime = 0;
bool life = true, check_win = false;
float myTime;

Texture tileset;
Sprite s_map;
Event event;
SoundBuffer buffer;
Music music;