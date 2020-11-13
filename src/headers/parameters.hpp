#include "maps.hpp"

int W_window = 400, H_window = 250;     // Размеры окна
int W_desktop = 0, H_desktop = 0;       // Разрешение монитора
int game_state = 0, menu_state = 0;     // игровые состояния
int game_timer = 120, scores = 0, health = 3; // HUD индикаторы на экране: жизни, очки, время
int gen_trigger = 0, local_scores = 0, local_timer = 0; // реализация генератора
int win_size_check = 1; // счетчик кол-ва нажатий клавиатурн. сочет.(shortcut) смены разреш. окна игры  
bool start_var = false, kill_boost = false; // триггеры(переключатели): 
// startvar - если только начал играть(исключаем ошибку при нажатии продолжить в меню паузы);
// kill_boost - если ГГ под бустом(большой Марио) столкнулся с врагом, данный триггер откл. буст и запускает таймер(2 сек),
// дающий возможность отойти от врага и не умереть.
bool im_host=false, im_client=false;    // триггеры для инициализации сетевого режима и определения ролей
float playtime = 0, myTime = 0, kill_boost_timer = 0; // счетчики времени:
// playtime - приводит отсчет времени к секундам, необходима для создания таймера обратного отсчета в HUD индикаторах,
// если playtime = 120, то game_timer = 0, тогда уровень проигран;
// myTime - отсчет времени в милисекундах (делется на 800 для плавности перемещения ГГ);
// kill_boost_timer - таймер отсчета когда ГГ на бусте столкнулся с врагом (2 сек).

// Встроенные в библиотеку SFML типы данных
Texture tileset, bg_tex;                    // текстуры
Sprite s_map, bg_sprite, menu_image;        // спрайты = объект + текстура
Font font;                                  // шрифт
Text text("", font, 20);                    // текст
Event event;                                // обработчик событий
SoundBuffer buffer;                         // буфер звука
Sound sound(buffer);                        // Обработка звука
Music music;                                // Обработка фоновой мелодии 

// Встроенные сетевые типы данных 
TcpSocket socket;                           // server 
TcpSocket host;                             // server
TcpSocket client;                           // client

// Создание окна
RenderWindow window(VideoMode(W_window, H_window),"Mario_project");
