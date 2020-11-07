BIN_1 := Mario_project
SOURCES_1 := src/main.cpp
HEADER_1 := src/header.hpp 
HEADER_2 := src/parameters.hpp
CC := g++
CFLAGS :=
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


$(BIN_1): $(SOURCES_1) $(HEADER_1) $(HEADER_2)
	clear && $(CC) $(SOURCES_1) -o $(BIN_1) $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf $(BIN_1)