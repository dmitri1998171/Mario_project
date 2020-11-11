#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <iostream>

const int H = 17, W = 150;          // Размеры карты
float offsetX = 0, offsetY = 0;     // Смещение для камеры
float lvl = 1;                    // Текущий уровень

using namespace std;
using namespace sf;
String TileMap[H] = {};

// Уровень 1
String TileMap1[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000  0000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                          w  i                                                                      0",
"0                                                                           i i i    w                                                   w           0",
"0         w                                  w                      k      kkkkkkk                                                                   0",
"0                            w                                      k                                            w                                   0",
"0                                                                   k   r                                                                            0",
"0                                                                   k0                         w                                                     0",
"0                                                                   k                                                                                0",
"0                                                    ii             k                                   r                                U           0",
"0             i                                t0                   k                                    r                                           0",
"0            i i                               00                   kii                            r      r                                          0",
"0           i   i                              00   kkck          kkkkkk                         rir       r                                         0",
"0           i   i              t0              T0   ii                                         r rirrr      r                                        0",
"0        i            g        00              T0                d                           r r riri        r       d     g                         0",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP      PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP     PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP      PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 

// Уровень 1.5
String TileMap1_5[H] = {
"                        0  ",
"0                       0  ",
"0                  w    0  ",
"0                       0  ",
"0                       0  ",
"0     w                 0  ",
"0                       0  ",
"0                       0  ",
"0                       0  ",
"0                       0  ",
"0                       0  ",
"0                     t00  ",
"0                  q00000  ",
"0        g         0   00  ",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 

// Уровень 2
String TileMap2[H] = {
"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKT0KK",
"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK KKKKKKKKKKKKKKKK KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKT0KK",
"0         KKKKKKK                    K                  KK KKKKK                        K                                                         T0KK",
"0          KKK                      K                                                   Ki                                                        T0KK",
"0             K                                                                         Kii            p                     K                    T0KK",
"0                                                                                       KKKKi           R        KKK    K  KK                     T0KK",
"0                                                                                       K iKKKK          RRR       K   K K K                      T0KK",
"0                                                                       R              K      K             KKK    K  K i KK                      T0KK",
"0                                                                      RR              K      K             KKK  K  KK iii                        T0KK",
"0                                                                     RiR      2       K  iiiiK                 KK      i  K                      T0KK",
"0                          iiii         2  2  2  2                   RRiR               K KKKKKR         K   KKKKKKK   KpRKKK                     T0KK",
"0          KcKcK        K iKKKKi K                                  RRiiR               K               KKK  KKKpppppppppp                        T0KK",
"0                       KKKK  KKKK                                 RRRiRR               K               KKKKKKpKrrppprp                        q  T0KK",
"0                                                                 RRRRi 1                              KKKKKKKKKKKKKKKKKKKKK                      T0KK",
"pppppppppppppppppppppppppppppppppppppppp  1  1  1  ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp",
"pppppppppppppppppppppppppppppppppppppppp           ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp",
"pppppppppppppppppppppppppppppppppppppppp           ppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp",
}; 

// Уровень 2.5
String TileMap2_5[H] = {
"              0000000000000",
"0                         r",
"0                        rr",
"0                  w    rrr",
"0                      rrrr",
"0     w               rrrrr",
"0                    rrrrrr",
"0                   rrrrrrr",
"0                  rrrrrrrr",
"0                 rrrrrrrrr",
"0                rrrrrrrrrr",
"0               rrrrrrrrrrr",
"0  m           rrrrrrrrrrrr",
"0        d    rrrrrrrrrrrrr",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 


// уровень 3
String TileMap3[H] = {
"                  w      ",    
"                         ",
"    w                    ",
" iiiiiiiiiiiiiiiiiiiiiii ",
" iiiiiiiiiiiiiiiiiiiiiii ",
"                    w    ",
" RRRRR    RRRRR  RRRR    ",
"                         ",
"    RRR    RRR  RRRRRRRR ",
"w                        ",
" RRRRRRR     RRRRRRRR    ",
"           w             ",
"    RRRRR   RRRRRRRRRRRR ",
"                         ",
" RRRRRRR  RRRRRRRRRRR    ",
"                 w       ",
"                         ",
}; 
