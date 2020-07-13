# include "ConsoleGameEngine.h"

class Game : public ConsoleGameEngine {
    unsigned long lastran;
    
    virtual void start() {
        TextFile file(this);
        file.open(absolute_path("lastran.txt"));
        lastran = (get_current_time() - std::stol(file.readlines()[0])) / 1000;
        file.write(std::to_string(get_current_time()));
    }

    virtual void update() {
        draw(0, 0, std::to_string(lastran) + "s ago");

        flush();
        clear();
    }
};

int main() {
    Game game;
    game.construct_console(64, 1);
}
