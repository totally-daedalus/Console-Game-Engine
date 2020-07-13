# ifndef CONSOLEGAMEENGINE_H
# define CONSOLEGAMEENGINE_H

# include <ncurses.h>
# include <string>
# include <vector>
# include <unistd.h>
# include <iostream>
# include <cmath>
# include <chrono>
# include <fstream>
# include <experimental/filesystem>

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

# define K_UP 259
# define K_DOWN 258
# define K_RIGHT 261
# define K_LEFT 260

# define K_ENTER 10

# define K_ESCAPE 27

# define K_F1 265
# define K_F2 266
# define K_F3 267
# define K_F4 268
# define K_F5 269
# define K_F6 270
# define K_F7 271
# define K_F8 272
# define K_F9 273
# define K_F10 274
# define K_F11 275
# define K_F12 276

# define K_BACKTICKS 96

# define K_0 48
# define K_1 49
# define K_2 50
# define K_3 51
# define K_4 52
# define K_5 53
# define K_6 54
# define K_7 55
# define K_8 56
# define K_9 57

# define K_TILDE 126

# define K_EXCLAMATION_MARK 33
# define K_AT_SIGN 64
# define K_NUMBER_SIGN 35
# define K_DOLLAR_SIGN 36
# define K_PERCENT_SIGN 37
# define K_CIRCUMFLEX 94
# define K_AMPERSAND 38
# define K_ASTERISK 42
# define K_STARTING_ROUND_BRACKET 40
# define K_ENDING_ROUND_BRACKET 41

# define K_UNDERLINE 95
# define K_MINUS 45
# define K_PLUS 43
# define K_EQUAL 61

# define K_BACKSPACE 263

# define K_TAB 9

# define K_LOWERCASE_A 97
# define K_LOWERCASE_B 98
# define K_LOWERCASE_C 99
# define K_LOWERCASE_D 100
# define K_LOWERCASE_E 101
# define K_LOWERCASE_F 102
# define K_LOWERCASE_G 103
# define K_LOWERCASE_H 104
# define K_LOWERCASE_I 105
# define K_LOWERCASE_J 106
# define K_LOWERCASE_K 107
# define K_LOWERCASE_L 108
# define K_LOWERCASE_M 109
# define K_LOWERCASE_N 110
# define K_LOWERCASE_O 111
# define K_LOWERCASE_P 112
# define K_LOWERCASE_Q 113
# define K_LOWERCASE_R 114
# define K_LOWERCASE_S 115
# define K_LOWERCASE_T 116
# define K_LOWERCASE_U 117
# define K_LOWERCASE_V 118
# define K_LOWERCASE_W 119
# define K_LOWERCASE_X 120
# define K_LOWERCASE_Y 121
# define K_LOWERCASE_Z 122

# define K_UPPERCASE_A 65
# define K_UPPERCASE_B 66
# define K_UPPERCASE_C 67
# define K_UPPERCASE_D 68
# define K_UPPERCASE_E 69
# define K_UPPERCASE_F 70
# define K_UPPERCASE_G 71
# define K_UPPERCASE_H 72
# define K_UPPERCASE_I 73
# define K_UPPERCASE_J 74
# define K_UPPERCASE_K 75
# define K_UPPERCASE_L 76
# define K_UPPERCASE_M 77
# define K_UPPERCASE_N 78
# define K_UPPERCASE_O 79
# define K_UPPERCASE_P 80
# define K_UPPERCASE_Q 81
# define K_UPPERCASE_R 82
# define K_UPPERCASE_S 83
# define K_UPPERCASE_T 84
# define K_UPPERCASE_U 85
# define K_UPPERCASE_V 86
# define K_UPPERCASE_W 87
# define K_UPPERCASE_X 88
# define K_UPPERCASE_Y 89
# define K_UPPERCASE_Z 89

# define K_STARTING_CURLY_BRACKET 123
# define K_ENDING_CURLY_BRACKET 125
# define K_STARTING_SQUARE_BRACKET 91
# define K_ENDING_SQUARE_BRACKET 93

# define K_BACKSLASH 92
# define K_SLASH 47
# define K_VERTICAL_BAR 124
# define K_SEMICOLON 59
# define K_COLON 58
# define K_QUOTATION_MARK 34
# define K_APOSTROPHE 39
# define K_COMMA 44
# define K_PERIOD 46
# define K_LESS_THAN 60
# define K_GREATER_THAN 62
# define K_QUESTION_MARK 63

# define K_SPACE 32

# define K_INSERT 331
# define K_DELETE 330
# define K_HOME 262
# define K_END 360
# define K_PAGE_UP 339
# define K_PAGE_DOWN 338

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

        class TextFile {
            private:

                std::string path;
                ConsoleGameEngine *engine;

            public:

                TextFile(ConsoleGameEngine *engine_) {
                    engine = engine_;
                }

                std::vector<std::string> readlines() {
                    std::ifstream file(path);
                    std::vector<std::string> lines;
                    std::string line;
                    while(getline(file, line)) {
                        lines.push_back(line);
                    }
                    file.close();
                    return lines;
                }

                std::string readline(int index) {
                    std::ifstream file(path);
                    std::string line;
                    int i = 0;
                    while(getline(file, line)) {
                        if(i == index) {
                            file.close();
                            return line;
                        }

                        i++;
                    }
                    engine -> close("Provided index (" + std::to_string(index) + ") is invalid");
                }

                int file_length() {
                    std::ifstream file(path);
                    std::string line;
                    int size = 0;
                    while(getline(file, line)) {
                        size++;
                    }
                    file.close();
                    return size;
                }

                void write(std::vector<std::string> lines) {
                    std::ofstream file(path);
                    for(int i = 0; i < lines.size(); i++) {
                        if(i != 0) {
                            file << std::endl;
                        }

                        file << lines[i];
                    }
                    file.close();
                }

                void append(std::vector<std::string> lines) {
                    if(file_length() == 1) {
                        write(lines);
                    } else {
                        std::ofstream file(path, std::ios_base::app);
                        for(int i = 0; i < lines.size(); i++) {
                            file << lines[i] << std::endl;
                        }
                        file.close();
                    }
                }
            
                void write(std::string line) {
                    std::ofstream file(path);
                    file << line;
                    file.close();
                }

                void append(std::string line) {
                    std::ofstream file(path, std::ios_base::app);
                    file << line;
                    file.close();
                }

                void replace(int index, std::string replace) {
                    std::vector<std::string> lines = readlines();

                    if(index > lines.size() || index < 0) {
                        engine -> close("Provided index (" + std::to_string(index) + ") is invalid");
                    }

                    lines[index] = replace;

                    write(lines);
                }

                void replace(std::string find, std::string replace) {
                    std::vector<std::string> lines = readlines();

                    for(int i = 0; i < lines.size(); i++) {
                        if(lines[i] == find) {
                            lines[i] = replace;
                            write(lines);
                            return;
                        }
                    }

                    engine -> close("The string to find (" + find + ") cannot be found.");
                }

                std::string get_path() {
                    return path;
                }

                void open(std::string path_) {
                    path = path_;
                    std::ofstream file(path, std::ios_base::app);
                    if(!file.is_open()) {
                        engine -> close("Provided path (" + path + ") is invalid.");
                    }
                    file.close();
                }
        };

        class Timer {
            private:

                unsigned long target_time;
                unsigned long wait_time = 0;

                unsigned long get_current_time() {
                    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                }

            public:

                void reset(unsigned long milli) {
                    wait_time = milli;
                    target_time = get_current_time() + wait_time;
                }

                void reset() {
                    target_time = get_current_time() + wait_time;
                }

                void start(unsigned long milli) {
                    reset(milli);
                }

                bool time_up() {
                    if(get_current_time() >= target_time) {
                        return true;
                    }

                    return false;
                }
        };

        std::string absolute_path() {
            std::string path = std::experimental::filesystem::current_path();
            return path + "/";
        }

        std::string absolute_path(std::string path) {
            return absolute_path() + path;
        }

        bool get_key(int keycode) {
            return event.get_key(keycode);
        }

        unsigned long get_current_time() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        template <class num>
        num get_random(num range1, num range2) {
            return rand() % (range2 + 1 - range1) + range1;
        }

        void construct_console(int width, int height) {
            screenWidth = width;
            screenHeight = height;

            srand((unsigned)get_current_time());
            
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
