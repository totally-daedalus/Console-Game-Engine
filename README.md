# Console Game Engine
It is a game engine, but it's ran in the console

**Please note that the Console Game Engine currently only works on linux. Versions for windows is hopefully coming soon.**
# How To Use
Just drag the header file into your projects.
# Examples
You can find more examples in the source/examples folder.

```cpp
# include "ConsoleGameEngine.h" // include my header file

class Game : public ConsoleGameEngine { // inherit the ConsoleGameEngine class
    int x = 1;
    int y = 0;
    int speed = 1;

    // start function will be called as soon as the game starts
    virtual void start() {
        create_pair(1, GREEN, BLACK); // creates a color pair with green text and black background with the id 1
        create_pair(2, YELLOW, BLACK); // creates a color pair with yellow text and black background with the id 2
        create_pair(3, BLUE, BLACK); // creates a color pair with blue text and black background with the id 3
    }

    // update function will be called every game update
    virtual void update() {
        if(get_key(K_RIGHT)) { // detects the right key
            x += speed;

            if(x > get_width() - 2) {
                x = 1;
            }
        }

        if(get_key(K_LEFT)) { // detects the left key
            x -= speed;

            if(x < 1) {
                x = get_width() - 2;
            }
        }

        draw(x, y, "#", get_pair(1)); // draw function draws player at (x, y) with the color pair 1 (green and black)

        draw(0, 0, "|", get_pair(2)); // draw function draws wall at (0, 0) with the color pair 2 (yellow and black)
        draw(get_width() - 1, 0, "|", get_pair(3)); // draw function draws wall at (width - 1, 0) with the color pair 3 (blue and black) the get_width function returns the screen width

        flush(); // puts everything on the screen
        clear(); // clears the screen
    }
};

int main() {
    Game game; // makes a Game object
    game.construct_console(20, 1); // makes a console with a width of 20 and a height of 1
}
```
