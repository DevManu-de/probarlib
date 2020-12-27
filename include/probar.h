/* See LICENSE file for copyright and license details. */

#ifndef _PROBAR_H
#define _PROBAR_H

typedef struct {

    unsigned int term_width;
    char indicator;
    char *text;
    unsigned int progress;

} progress_bar;

/* See README.md for more info */
progress_bar *bar_create(unsigned int term_width, char indicator, char *text);
void bar_set_progress(progress_bar *bar, unsigned int progress);
int bar_print(progress_bar *bar);
void bar_set_width(progress_bar *bar, unsigned int term_width);
unsigned int bar_get_progress(progress_bar *bar);
void bar_set_text(progress_bar *bar, char *text);
void bar_destroy(progress_bar *bar);

#endif
