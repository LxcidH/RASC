/*
Copyright (c) <2025>, <Lxcid>
All rights reserved.

This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*/

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> // For NULLi
#include <time.h>

#define DELAY 120000
#define WIN_HEIGHT 20
#define WIN_WIDTH  40
#define PLAY_HEIGHT (WIN_HEIGHT - 2)
#define PLAY_WIDTH (WIN_WIDTH - 2)
#define MAX_SNAKE_LENGTH 684
#define MAX_APPLES 1

typedef struct {
    int x;
    int y;
} Point;

Point spawn_apple(Point *p) {
    int x = PLAY_WIDTH;
    int y = PLAY_HEIGHT;
    int xS = 1 + rand() % PLAY_WIDTH;
    int yS = 1 + rand() % PLAY_HEIGHT;
    p->x = xS;
    p->y = yS;
    return *p;
}

int endgame(WINDOW *game) {
    wclear(game);
    wattron(game, COLOR_PAIR(3));
    box(game, 0, 0);
    mvwprintw(game, WIN_HEIGHT / 2, (WIN_WIDTH - strlen("Game Over!")) / 2, "Game Over!");
    mvwprintw(game, (WIN_HEIGHT / 2) + 1, (WIN_WIDTH - strlen("  Press 'q' to quit or 'r' to replay!")) / 2, "  Press 'q' to quit or 'r' to replay!");
    wattron(game, COLOR_PAIR(3));
    wrefresh(game);
    while(1) {
        nodelay(stdscr, 0);
        int ch = getch();
        switch(ch) {
            case 'q':
                return 0;
            case 'r':
                return 1;
        }
    }
}

int wongame(WINDOW *game) {
    wclear(game);
    wattron(game, COLOR_PAIR(4));
    box(game, 0, 0);
    mvwprintw(game, WIN_HEIGHT / 2, (WIN_WIDTH - strlen("You Won!")) / 2, "You Won!");
    mvwprintw(game, (WIN_HEIGHT / 2) + 1, (WIN_WIDTH - strlen("  Press 'q' to quit or 'r' to replay!")) / 2, "  Press 'q' to quit or 'r' to replay!");
    wattron(game, COLOR_PAIR(4));
    wrefresh(game);
    while(1) {
        nodelay(stdscr, 0);
        int ch = getch();
        switch(ch) {
            case 'q':
                return 0;
            case 'r':
                return 1;
        }
    }
}

int snakeGame() {
        srand(time(NULL));
    WINDOW *game_win;
    WINDOW *stat_win;
    int start_x, start_y;
    int max_x, max_y;
    char direction = 'r';

    Point apples[MAX_APPLES];
    int apple_count = 0;
    int apples_collected = 0;

    Point snake[MAX_SNAKE_LENGTH];
    int snake_length = 3;

    snake[0] = (Point){5, 5};   // Head
    snake[1] = (Point){5, 6};
    snake[2] = (Point){5, 7};

    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    getmaxyx(stdscr, max_y, max_x);
    start_y = (max_y - WIN_HEIGHT) / 2;
    start_x = (max_x - WIN_WIDTH) / 2;
    game_win = newwin(WIN_HEIGHT, WIN_WIDTH, start_y, start_x);
    stat_win = newwin(4, WIN_WIDTH, (start_y + WIN_HEIGHT), start_x);

    if (game_win == NULL) {
        endwin();
        printf("Error: Terminal window is too small for the game (needs %dx%d).\n", WIN_WIDTH, WIN_HEIGHT);
        return 1;
    }

    while(1) {
        int ch = getch();
        switch(ch) {
            case KEY_UP:    case 'w': if (direction != 'd') direction = 'u'; break;
            case KEY_DOWN:  case 's': if (direction != 'u') direction = 'd'; break;
            case KEY_LEFT:  case 'a': if (direction != 'r') direction = 'l'; break;
            case KEY_RIGHT: case 'd': if (direction != 'l') direction = 'r'; break;
            case 'q':
                endwin();
                return 0;
        }

        for(int i = snake_length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        switch(direction) {
            case 'u': snake[0].y--; break;
            case 'd': snake[0].y++; break;
            case 'l': snake[0].x--; break;
            case 'r': snake[0].x++; break;
        }

        if(snake[0].x < 1 || snake[0].x > PLAY_WIDTH || snake[0].y < 1 || snake[0].y > PLAY_HEIGHT) {
                if(endgame(game_win) == 0) {
                    endwin();
                    return 0;
                } else {
                    endwin();
                    return 1;
                }
        }
        for(int i = 1; i < snake_length; i++) {
            if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                if(endgame(game_win) == 0) {
                    endwin();
                    return 0;
                } else {
                    endwin();
                    return 1;
                }
            }
        }

        for(int i = 0; i < apple_count; i++) {
            if(snake[0].x == apples[i].x && snake[0].y == apples[i].y) {
                 apple_count--;
                 apples_collected++;
                 snake_length++;
            }
        }

        if(snake_length == 5) {
            if(wongame(game_win) == 0) {
                endwin();
                return 0;
            } else {
                endwin();
                return 1;
            }
        }

        wclear(game_win);
        wclear(stat_win);



        wattron(game_win, COLOR_PAIR(2));
        box(game_win, 0, 0);
        mvwprintw(game_win, 0, (WIN_WIDTH - strlen(" Snake :3 ")) / 2, " Snake :3 ");
        wattroff(game_win, COLOR_PAIR(2));
        wattron(stat_win, COLOR_PAIR(2));
        box(stat_win, 0, 0);
        mvwprintw(stat_win, 0, (WIN_WIDTH - strlen(" Stats ")) / 2, " Stats ");
        mvwprintw(stat_win, 1, (WIN_WIDTH - strlen("Apples Collected:")) / 2, "Apples Collected: %d", apples_collected);
        mvwprintw(stat_win, 2, (WIN_WIDTH - strlen("Snake Length: %d")) / 2, "Snake Length: %d", snake_length);
        wattroff(stat_win, COLOR_PAIR(2));

        for(int i = 0; i < snake_length; i++) {
            char display_char = (i == 0) ? '@' : '#';
            wattron(game_win, COLOR_PAIR(2));
            mvwaddch(game_win, snake[i].y, snake[i].x, display_char);
            wattron(game_win, COLOR_PAIR(2));
        }

        if(apple_count < MAX_APPLES) {
            spawn_apple(&apples[0]);
            apple_count++;
        }

        for(int i = 0; i < apple_count; i++) {
            wattron(game_win, COLOR_PAIR(1));
            mvwaddch(game_win, apples[i].y, apples[i].x, 'A');
            wattron(game_win, COLOR_PAIR(1));
        }

        wrefresh(game_win);
        wrefresh(stat_win);

        usleep(DELAY);
    }

    endwin();
    return 0;
}

int main(int argc, char* argv[]) {
    if(snakeGame() == 1) {
        snakeGame();
    } else {
        return 0;
    }
}
