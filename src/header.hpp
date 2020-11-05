#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int H = 17, W = 150;          // Размеры карты
float offsetX = 0, offsetY = 0;     // смещение для тайлсета

using namespace sf;

// Бонус-уровень
String TileMapB[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                   w           0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                       kk                         w                                          0",
"0                                                                             k  k    k    k                                                         0",
"0                      c                                                      k      kkk  kkk  w                                                     0",
"0                                                                       r     k       k    k                                                         0",
"0                                                                      rr     k  k                                             U                     0",
"0                                                                     rrr      kk                                                                    0",
"0               c    kckck                                           rrrr0                     0                                                     0",
"0                                      t0                           rrrrr                                                                            0",
"0g                                     00              t0          rrrrrr            g                                                       t0      0",
"0           d    g       d             00              00         rrrrrrr                                        d     g                     00      0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 

// Уровень 1
String TileMap[H] = {
"00000000000000000000000000000000000000000000000000000000                                   00000000000000000000000000000000000000000000000000000000000",
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
"0                     g        00              T0                d                           r r riri        r       d     g                         0",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP      PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP     PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPP   PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP      PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 

// Уровень 2
String TileMap2[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                   w           0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                                                  w                                          0",
"0                                                                                                                                                    0",
"0                      c                                                                       w                                                     0",
"0                                                                       r                                                                            0",
"0                                                                      rr                                                      U                     0",
"0                                                                     rrr                                                                            0",
"0                                                                    rrrr                      0                                                     0",
"0                                      t0                           rrrrr                                                                            0",
"0g                                     00              t0          rrrrrr                                                                    t0      0",
"0                                      00              00         rrrrrrr                                        d     g                     00      0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 