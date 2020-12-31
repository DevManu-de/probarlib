/* See LICENSE file for copyright and license details. */

#ifndef _PROBAR_H
#define _PROBAR_H

#include <time.h>
#include <unistd.h>

unsigned int get_term_width();

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
    unsigned int max_value;
    unsigned int progress;
    struct {

        char left_bar_boder;
        char indicator;
        char head;
        char unfinished;
        char right_bar_border;

    } bar;
    unsigned int eta : 1;
    time_t ETA_START;
    time_t ETA_STOP;
    unsigned int text_bar_gap;


} complex_progress_bar;

/* See examples/BasicProgressBar/README.md for more info */
typedef complex_progress_bar basic_progress_bar;
#define basic_bar_create() complex_bar_create()
#define basic_bar_set_bar_attributes(bbar_pntr, text) complex_bar_set_bar_attributes(bbar_pntr, 0, text, '[', '#', ' ', ' ', ']', 0, 10, 100)
#define basic_bar_set_progress(bbar_pntr, progress) complex_bar_set_progress(bbar_pntr, progress)
#define basic_bar_print(bbar_pntr) complex_bar_print(bbar_pntr)
#define basic_bar_set_text(bbar_pntr, text) complex_bar_set_text(bbar_pntr, text)
#define basic_bar_get_progress(bbar_pntr) complex_bar_get_progress(bbar_pntr)
#define basic_bar_destroy(bbar_pntr) complex_bar_destroy(bbar_pntr)

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
                                   unsigned int text_bar_gap, unsigned int max_value);
void complex_bar_start_eta(complex_progress_bar *cbar);
double complex_bar_get_duration(complex_progress_bar *cbar);
void complex_bar_set_progress(complex_progress_bar *cbar, unsigned int progress);
int complex_bar_print(complex_progress_bar *cbar);
void complex_bar_set_width(complex_progress_bar *cbar, unsigned int width);
void complex_bar_set_text(complex_progress_bar *cbar, char *fromat, ...);
int complex_bar_get_progress(complex_progress_bar *cbar);
void complex_bar_destroy(complex_progress_bar *cbar);


#endif
