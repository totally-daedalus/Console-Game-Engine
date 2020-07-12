# include "ConsoleGameEngine.h"

class Game : public ConsoleGameEngine {
    long timer;

    int second = 0;

    virtual void start() {
        timer = get_current_time() + 1000;
    }

    virtual void update() {
        if(get_current_time() > timer) {
            second++;
            timer = get_current_time() + 1000;
        }

        draw(0, 0, std::to_string(second) + ":" + std::to_string(get_current_time() % 1000));

        flush();
        clear();
    }
};

int main() {
    Game game;
    game.construct_console(20, 1);
}
