#ifndef _PROBAR_H
#define _PROBAR_H

typedef struct {

    unsigned int term_width;
    char indicator;
    const char *text;
    unsigned int progress;

} progressbar;

progressbar *create_bar(unsigned int term_width, char indicator, char *text);
void set_bar_progress(progressbar *bar, unsigned int progress);
int print_bar(progressbar *bar);
void set_bar_width(progressbar *bar, unsigned int term_width);
unsigned int get_progress(progressbar *bar);
void destroy_bar(progressbar *bar);

#endif
