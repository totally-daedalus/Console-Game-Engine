# ifndef CONSOLEGAMEENGINE_H
# define CONSOLEGAMEENGINE_H

# include <ncurses.h>
# include <string>
# include <vector>
# include <unistd.h>
# include <iostream>
# include <cmath>
# include <chrono>

# define NORMAL A_NORMAL
# define STANDOUT A_STANDOUT
# define UNDERLINE A_UNDERLINE
# define REVERSE A_REVERSE
# define BLINK A_BLINK
# define DIM A_DIM
# define BOLD A_BOLD
# define PROTECT A_PROTECT
# define INVIS A_INVIS
# define ALTCHARSET A_ALTCHARSET
# define CHARTEXT A_CHARTEXT

# define BLACK COLOR_BLACK
# define BLUE COLOR_BLUE
# define GREEN COLOR_GREEN
# define CYAN COLOR_CYAN
# define RED COLOR_RED
# define MAGENTA COLOR_MAGENTA
# define YELLOW COLOR_YELLOW
# define WHITE COLOR_WHITE

# define K_UP KEY_UP
# define K_DOWN KEY_DOWN
# define K_RIGHT KEY_RIGHT
# define K_LEFT KEY_LEFT

# define K_ENTER 10

# define K_ESCAPE 27

class ConsoleGameEngine {
    private:
        
        class Event {
            private:

                std::vector<int> keys = std::vector<int>();
            
            public:

                void update() {
                    keys.clear();
    
                    int key;
    
                    while((key = getch()) != ERR) {
                        keys.push_back(key);
                    }
                }

                bool get_key(int keycode) {
                    for(int i = 0; i < keys.size(); i++) {
                        if(keys[i] == keycode) {
                            return true;
                        }
                    }

                    return false;
                }
        };

        int TARGET_FPS = 60;
        int FPS_PER_SECOND = 1 / 60;

        WINDOW *window;

        int startx = 0;
        int starty = 0;
        int screenWidth;
        int screenHeight;

        Event event;

        std::vector<std::vector<char>> pixels = std::vector<std::vector<char>>();
        std::vector<std::vector<int>> attributes = std::vector<std::vector<int>>();
        std::vector<std::vector<int>> attributes1 = std::vector<std::vector<int>>();
        
        void init_vector() {
            std::vector<char> column = std::vector<char>();
            std::vector<int> columnint = std::vector<int>();

            for(int i = 0; i < screenWidth; i++) {
                columnint.push_back(NORMAL);
            }

            for(int i = 0; i < screenWidth; i++) {
                column.push_back(' ');
            }

            for(int i = 0; i < screenHeight; i++) {
                attributes.push_back(columnint);
            }

            for(int i = 0; i < screenHeight; i++) {
                attributes1.push_back(columnint);
            }

            for(int i = 0; i < screenHeight; i++) {
                pixels.push_back(column);
            }
        }

        void loop() {
            while(true) {
                update();
                event.update();
                usleep(FPS_PER_SECOND * 1000000);
            }

            close();
        }

    public:

        bool get_key(int keycode) {
            return event.get_key(keycode);
        }

        void construct_console(int width, int height) {
            screenWidth = width;
            screenHeight = height;
            
            init_vector();

            initscr();

            if(has_colors() == FALSE) {
                close("Your ternimal does not support color");
            }

            start_color();
            
            curs_set(0);
            cbreak();
            nodelay(stdscr, TRUE);
            noecho();

            keypad(stdscr, TRUE);

            window = newwin(height, width, starty, startx);

            wrefresh(window);

            start();
            loop();
        }
        
        void show_cursor() {
            curs_set(1);
        }

        void hide_cursor() {
            curs_set(0);
        }

        void create_pair(int id, int color1, int color2) {
            init_pair(id, color1, color2);
        }

        int get_pair(int id) {
            return COLOR_PAIR(id);
        }

        void draw(int x, int y, char character) {
            if(x > screenWidth - 1)
                close("Passed in x value (" + std::to_string(x) + ") of draw function is too big");
            if(y > screenHeight - 1)
                close("Passed in y value (" + std::to_string(y) + ") of draw function is too big");

            pixels[y][x] = character;
        }

        void draw(int x, int y, char character, int colorcode) {
            draw(x, y, character);
            attributes[y][x] = colorcode;
        }

        void draw(int x, int y, char character, int colorcode, int colorcode1) {
            draw(x, y, character);
            attributes[y][x] = colorcode;
            attributes1[y][x] = colorcode1;
        }

        void draw(int x, int y, std::string string) {
            for(int i = 0; i < string.size(); i++) {
                draw(x + i, y, string[i]);
            }
        }

        void draw(int x, int y, std::string string, int colorcode) {
            for(int i = 0; i < string.size(); i++) {
                draw(x + i, y, string[i], colorcode);
            }
        }

        int get_width() {
            return screenWidth;
        }

        int get_height() {
            return screenHeight;
        }

        long get_current_time() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        void flush() {
            for(int i = 0; i < screenWidth; i++) {
                for(int j = 0; j < screenHeight; j++) {
                    wattron(window, attributes[j][i]);
                    wattron(window, attributes1[j][i]);
                    mvwaddch(window, j, i, pixels[j][i]);
                    wattroff(window, attributes[j][i]);
                    wattroff(window, attributes1[j][i]);
                }
            }

            wrefresh(window);
        }

        void clear() {
            for(int i = 0; i < screenWidth; i++) {
                for(int j = 0; j < screenHeight; j++) {
                    pixels[j][i] = ' ';
                }
            }
        }

        void close() {
            delwin(window);
            endwin();
            exit(0);
        }

        void close(std::string errormessage) {
            delwin(window);
            endwin();
            std::cout << errormessage << std::endl;
            exit(1);
        }
        
        virtual void start() {};
        virtual void update() {};
};

# endif
