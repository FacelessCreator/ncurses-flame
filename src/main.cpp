#include <chrono>
#include <thread>
#include <locale.h>

#include "flame.h"

int main() {

    setlocale(LC_ALL, ""); // make unicode works

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    start_color();
    clear();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    Flame flame = Flame(COLS, LINES);

    //attron(COLOR_PAIR(3));

    while (1)
    {
        int c = getch();
        if (c == 'q') {
            endwin();
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(66));

        flame.tick();
        flame.draw();
        
    }

}
