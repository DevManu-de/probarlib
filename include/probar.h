/* See LICENSE file for copyright and license details. */

#ifndef _PROBAR_H
#define _PROBAR_H

typedef struct {

    unsigned int term_width;
    char indicator;
    char *text;
    unsigned int progress;

} progressbar;

/* See README.md for more info */
progressbar *bar_create(unsigned int term_width, char indicator, char *text);
void bar_set_progress(progressbar *bar, unsigned int progress);
int bar_print(progressbar *bar);
void bar_set_width(progressbar *bar, unsigned int term_width);
unsigned int bar_get_progress(progressbar *bar);
void bar_set_text(progressbar *bar, char *text);
void bar_destroy(progressbar *bar);

#endif
