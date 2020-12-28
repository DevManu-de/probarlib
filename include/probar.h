/* See LICENSE file for copyright and license details. */

#ifndef _PROBAR_H
#define _PROBAR_H

#include <unistd.h>

unsigned int get_term_width();

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
    unsigned int is_stopped : 1;

} progress_indicator;

typedef struct __complex_progress_bar {

    unsigned int term_width;
    char *text;
    unsigned int progress;
    struct {

        char left_bar_boder;
        char indicator;
        char head;
        char unfinished;
        char right_bar_border;

    } bar;
    unsigned int eta : 1;
    unsigned int text_bar_gaps;
    char *positioning;


} complex_progress_bar;

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
int indicator_stop(progress_indicator *indicator);
void indicator_destroy(progress_indicator *indicator);

/* See examples/ComplexProgressBar/README.md for more info */
complex_progress_bar *complex_bar_create();
int complex_bar_set_bar_attributes(complex_progress_bar *cbar, unsigned int term_width, char *text,
                                    char left_bar_border, char indicator,
                                    char head, char unfinished,
                                    char right_bar_border, unsigned int eta,
                                    unsigned int text_bar_gaps, char *positioning);
void complex_bar_set_progress(complex_progress_bar *cbar, unsigned int progress);
int complex_bar_print(complex_progress_bar *cbar);
void complex_bar_set_width(complex_progress_bar *cbar, unsigned int width);
int complex_bar_set_text(complex_progress_bar *cbar, char *text);
int complex_bar_get_progress(complex_progress_bar *cbar);
void complex_bar_destroy(complex_progress_bar *cbar);


#endif
