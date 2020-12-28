/* See LICENSE file for copyright and license details. */

#include <sys/mman.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "probar.h"

void *create_shared_memory(size_t size);

unsigned int get_term_width()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_col;

}


/* Here begins the part of progress bar */
progress_bar *bar_create(unsigned int term_width, char indicator, char *text)
{
    progress_bar *bar = malloc(sizeof(progress_bar));
    if (bar == NULL)
        return NULL;
    bar->indicator = indicator;
    bar->progress = 0;
    bar->term_width = term_width;
    bar->text = strdup(text);

    return bar;

}
void bar_set_progress(progress_bar *bar, unsigned int progress)
{
    bar->progress = progress;

}

void bar_set_width(progress_bar *bar, unsigned int term_width)
{
    bar->term_width = term_width;

}

int bar_print(progress_bar *bar)
{

    /* Check if term_width is large enough */
    if ((int) (bar->term_width - strlen(bar->text) - 17) <= 0)
        return -1;
    /* This is only the bar it self */
    unsigned int bar_width = bar->term_width - strlen(bar->text) - 17;
    /* This is how much one indicator affects the progress */
    float chars_per_iter = (float) bar_width / 100;
    float chars = 0.0;
    unsigned int chars_printed = 0;

    /* Print the first part of the  */
    printf("\r%s          %3d%% [", bar->text, bar->progress);
    unsigned int i;
    for (i = 0; i < bar->progress; i++)
    {
        chars += chars_per_iter;
        /* Only print characters if 1 char is 1 char in the terminal  */
        if (chars >= 1)
        {
            int j;
            for (j = 0; j < chars; j++)
            {
                printf("%c", bar->indicator);
                chars--;
                chars_printed++;
            }
        }
    }

    /* In some cases the bar doesnt completely fill because the last char is not >= 1 */
    if (chars_printed < bar_width)
    {
        putc(bar->indicator, stdout);
        chars_printed++;
    }

    /* Prints the remaining whitespaces  */
    for (i = 0; i < bar_width - chars_printed; i++)
    {
        putc(' ', stdout);
    }
    /* End the bar and flush stdout */
    putc(']', stdout);
    fflush(stdout);
    return 0;

}

void bar_set_text(progress_bar *bar, char *text)
{
    free(bar->text);
    bar->text = strdup(text);

}


unsigned int bar_get_progress(progress_bar *bar)
{
    return bar->progress;
}

void bar_destroy(progress_bar *bar)
{
    free(bar);
}

/* Here ends the part of progress bar */

/* Here begins the part of progress indicator */
progress_indicator *indicator_create(unsigned int term_width, char *text, unsigned int max_text_size)
{
    progress_indicator *indicator = malloc(sizeof(progress_indicator));
    if (indicator == NULL)
        return NULL;
    /* Create a shared memory for the child to react to terminal changes*/
    indicator->term_width = create_shared_memory(sizeof(int));
    indicator->term_width[0] = term_width;

    /* The max_text_size needs to be set because the shared memory cannot be
     * realloced */
    indicator->max_text_size = max_text_size;

    /* Put text in shared memory for the child to update it later */
    indicator->text = create_shared_memory(indicator->max_text_size);
    memcpy(indicator->text, text, strlen(text) + 1);

    indicator->pid = 0;
    indicator->is_stopped = 0;
    return indicator;
}

int indicator_start(progress_indicator *indicator)
{
    /* Array for the animation */
    char circle[] = {'|', '/', '-', '\\'};
    unsigned int circle_position = 0;

    indicator->is_stopped = 0;
    /* Create a child process */
    indicator->pid = fork();
    if (indicator->pid == 0)
    {
        /* This is the child */

        while (indicator->is_stopped == 0)
        {
            /* Calculate gap between text and indicator */
            unsigned int text_indicator_gap = indicator->term_width[0] - strlen(indicator->text) - 1;
            /* Print text */
            printf("\r%s", indicator->text);

            /* Print spaces between text and indicator */
            unsigned int i;
            for (i = 0; i < text_indicator_gap; ++i)
            {
                putc(' ', stdout);
            }
            /* Print the correct circle position to make it look
             * like a real animation */
            putc(circle[circle_position], stdout);
            fflush(stdout);

            if (circle_position > 3)
                circle_position = 0;
            else
                circle_position++;

            usleep(150000);
        }
    }
    else if (indicator->pid > 0)
    {
        /* This is its parent */

    } else
    {
        /* Something failed */
        return -1;

    }

    return 0;
}
void indicator_set_text(progress_indicator *indicator, char *text)
{

    memcpy(indicator->text, text, strlen(text) + 1);


}

void indicator_set_width(progress_indicator *indicator, unsigned int term_width)
{

    indicator->term_width[0] = term_width;

}

int indicator_stop(progress_indicator *indicator)
{
    /* Kill the child and set is_stopped.
     * On successful kill kill returns 0.
     * On failed kill kill returns -1
     * so is_stopped always has the correct value */
    indicator->is_stopped = kill(indicator->pid, SIGTERM) + 1;
    putc('\n', stdout);

    return indicator->is_stopped;

}
void indicator_destroy(progress_indicator *indicator)
{
    /* If killing failed before then force
     * kill child now */
    if (indicator->is_stopped == 0)
        kill(indicator->pid, SIGKILL);
    /* Dealloc all shared memory */
    munmap(indicator->text, indicator->max_text_size);
    munmap(indicator->term_width, sizeof(int));
    /* Finally dealloc the pointer */
    free(indicator);

}

/* Here ends the part of progress indicator */

/* Here starts the part of complex progress bar */


complex_progress_bar *complex_bar_create()
{
    complex_progress_bar *cbar = malloc(sizeof(complex_progress_bar));
    return cbar == NULL ? NULL : cbar;

}


int complex_bar_set_bar_attributes(complex_progress_bar *cbar, unsigned int term_width, char *text,
                                   char left_bar_border, char indicator,
                                   char head, char unfinished,
                                   char right_bar_border, unsigned int eta,
                                   unsigned int text_bar_gaps, char *positioning)
{

    cbar->term_width = term_width;
    cbar->text = strdup(text);
    cbar->progress = 0;
    cbar->bar.left_bar_boder = left_bar_border;
    cbar->bar.indicator = indicator;
    cbar->bar.head = head;
    cbar->bar.unfinished = unfinished;
    cbar->bar.right_bar_border = right_bar_border;
    cbar->eta = eta;
    cbar->text_bar_gaps = text_bar_gaps;
    cbar->positioning = strdup(positioning);

    return cbar->text != NULL && cbar->positioning != NULL ? 0 : -1;
}

void complex_bar_set_progress(complex_progress_bar *cbar, unsigned int progress)
{

    cbar->progress = progress;

}

int complex_bar_print(complex_progress_bar *cbar)
{

   

}

void complex_bar_set_width(complex_progress_bar *cbar, unsigned int width);
int complex_bar_set_text(complex_progress_bar *cbar, char *text);
int complex_bar_get_progress(complex_progress_bar *cbar);
void complex_bar_destroy(complex_progress_bar *cbar);

/* Here ends the part of complex progress bar */

void *create_shared_memory(size_t size) {

    /* Make shared memory readable and writeable */
    int protection = PROT_READ | PROT_WRITE;
    /* Make shared memory only visible to its children */
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    /* Return pointer to shared memory */
    return mmap(NULL, size, protection, visibility, -1, 0);

}
