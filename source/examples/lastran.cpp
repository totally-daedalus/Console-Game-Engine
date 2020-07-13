# include "ConsoleGameEngine.h"

class Game : public ConsoleGameEngine {
    int lastran;
    
    virtual void start() {
        TextFile file(this);
        file.open("/home/hello/Projects/C++/consolegameengine/source/examples/lastran.txt"); // you have to change the path according to where you placed the project
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
