/* See LICENSE file for copyright and license details. */

#ifndef _PROBAR_H
#define _PROBAR_H

#include <unistd.h>

typedef struct __progress_bar {

    unsigned int term_width;
    char indicator;
    char *text;
    unsigned int progress;

} progress_bar;

typedef struct __progress_indicator {

    unsigned int *term_width;
    char *text;
    unsigned int max_text_size;
    pid_t pid;
    int is_stopped : 1;

} progress_indicator;

/* See examples/BasicProgressBar/README.md for more info */
progress_bar *bar_create(unsigned int term_width, char indicator, char *text);
void bar_set_progress(progress_bar *bar, unsigned int progress);
int bar_print(progress_bar *bar);
void bar_set_width(progress_bar *bar, unsigned int term_width);
unsigned int bar_get_progress(progress_bar *bar);
void bar_set_text(progress_bar *bar, char *text);
void bar_destroy(progress_bar *bar);

/* See examples/ProgressIndicatorCircle/README.md for more info */
progress_indicator *indicator_create(unsigned int term_width, char *text, unsigned int max_text_size);
int indicator_start(progress_indicator *indicator);
void indicator_set_text(progress_indicator *indicator, char *text);
void indicator_set_width(progress_indicator *indicator, unsigned int term_width);
void indicator_stop(progress_indicator *indicator);
void indicator_destroy(progress_indicator *indicator);

#endif
