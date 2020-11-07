BIN_1 := Mario_project
SOURCES_1 := src/main.cpp
HEADER_1 := src/headers/parameters.hpp 
HEADER_2 := src/headers/maps.hpp
HEADER_3 := src/headers/hero.hpp
HEADER_4 := src/headers/menu.hpp
HEADER_5 := src/headers/game_cycle.hpp
HEADER_6 := src/headers/hud.hpp
CC := g++
CFLAGS :=
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# $(HEADER_1) $(HEADER_2) $(HEADER_3) $(HEADER_4) $(HEADER_5) $(HEADER_6)

$(BIN_1): $(SOURCES_1) 
	clear && $(CC) $(SOURCES_1) $(CFLAGS) $(LDFLAGS) -o $(BIN_1)
clean:
	rm -rf $(BIN_1)