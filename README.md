# Console Game Engine
It is a game engine, but it's ran in the console

**Please note that the Console Game Engine currently only works on linux. Versions for windows is hopefully coming soon.**
# How To Use
Just drag the header file into your projects.
# Examples
You can find more examples in the source/examples folder.

`


#include "ConsoleGameEngine.h"

class Game : public ConsoleGameEngine {
    int x = 1;
    int y = 0;
    int speed = 1;

    virtual void start() {
        create_pair(1, GREEN, BLACK);
        create_pair(2, YELLOW, BLACK);
        create_pair(3, BLUE, BLACK);
    }

    virtual void update() {
        if(get_key(K_RIGHT)) {
            x += speed;

            if(x > get_width() - 2) {
                x = 1;
            }
        }

        if(get_key(K_LEFT)) {
            x -= speed;

            if(x < 1) {
                x = get_width() - 2;
            }
        }

        draw(x, y, "#", get_pair(1));

        draw(0, 0, "|", get_pair(2));
        draw(get_width() - 1, 0, "|", get_pair(3));

        flush();
        clear();
    }
};

int main() {
    Game game;
    game.construct_console(20, 1);
}


`
