#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define BUF_SIZE 1024
#define LINES_SZ 16
#define DX 1

#define MIN(x, y) ((x > y) ? (y) : (x))

void render(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        return;
    }

    WINDOW *win, *frame;

    setlocale(LC_ALL, "");

    size_t lines_sz = LINES_SZ;
    size_t line_count = 0;
    char **lines = malloc(lines_sz * sizeof(char*));
    char buffer[BUF_SIZE];

    while (fgets(buffer, BUF_SIZE, file)) {
        line_count++;
        
        if (line_count > lines_sz) {
            lines_sz += LINES_SZ;
            lines = realloc(lines, lines_sz * sizeof(char*));
        }

        lines[line_count - 1] = strdup(buffer);
    }

    fclose(file);

    initscr();
    noecho();
    cbreak();
    refresh();

    frame = newwin(LINES - 2*DX, COLS - 2*DX, DX, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), "");
    wrefresh(frame);

    win = newwin(LINES-2*DX - 2, COLS-2*DX - 2, DX + 1, DX + 1);

    int height = getmaxy(win) - 2;

    keypad(win, TRUE);
    scrollok (win, TRUE);

    printw("File: %s; lines: %ld\n", filename, line_count);
    refresh();

    size_t cur = 0;

    for (int i = 0; i < MIN(line_count, height); i++) {
        wprintw(win, "%*d: %s", 4, i, lines[i]);
    }

    wmove(win, 0, 0);

    for (int c = wgetch(win); c != 27; c = wgetch(win)) {
        werase(win);

        if (c == KEY_UP && cur != 0) {
            cur--;
        } else if ((c == KEY_DOWN || c == ' ') && cur + height < line_count) {
            cur++;
        }

        for (int i = cur; i < cur + MIN(line_count, height); i++) {
            wprintw(win, "%*d: %s", 4, i, lines[i]);
        }
        wmove(win, 0, 0);
    }

    delwin(win);
    delwin(frame);
    endwin();

    for (size_t i = 0; i < lines_sz; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    render(argv[1]);
    return 0;
}
