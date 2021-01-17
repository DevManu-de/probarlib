/* See LICENSE file for copyright and license details. */

#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
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
                                   unsigned int text_bar_gap, unsigned int max_value)
{

    cbar->term_width = term_width;
    cbar->text = malloc(get_term_width());
    complex_bar_set_text(cbar, text);
    cbar->progress = 0;
    cbar->bar.left_bar_boder = left_bar_border;
    cbar->bar.indicator = indicator;
    cbar->bar.head = head;
    cbar->bar.unfinished = unfinished;
    cbar->bar.right_bar_border = right_bar_border;
    cbar->eta = eta;
    cbar->text_bar_gap = text_bar_gap;
    cbar->max_value = max_value;

    return cbar->text != NULL ? 0 : -1;
}

void complex_bar_start_eta(complex_progress_bar *cbar)
{

    cbar->ETA_START = time(NULL);

}

double complex_bar_get_duration(complex_progress_bar *cbar)
{

    return difftime(cbar->ETA_STOP, cbar->ETA_START);

}

void complex_bar_set_progress(complex_progress_bar *cbar, unsigned int progress)
{

    cbar->progress = progress;

}

int complex_bar_print(complex_progress_bar *cbar)
{

    if (cbar->progress == cbar->max_value)
        cbar->ETA_STOP = time(NULL);

    /* Determine if automatic resizing is used */
    int term_width;
    if (cbar->term_width == 0)
        term_width = get_term_width();
    else
        term_width = cbar->term_width;

    /* Get with of only the bar.        The 7 comes from the percentage (3 characters) a %, a space and the bar borders */
    int bar_width = (unsigned int) (term_width - strlen(cbar->text) - cbar->text_bar_gap - 7 /* - ETA */);
    if (cbar->eta != 0)
        bar_width -= 11;

    if (bar_width <= 0)
        return -1;

    //unsigned int cbar->max_value = cbar->max_value;
    /* Calculate how much 1% affects the bar in real */
    float chars_per_iter = (float) bar_width / cbar->max_value;
    float chars = 0.0;
    int chars_printed = 0;

    /* Print text */
    printf("\r%s", cbar->text);

    /* Print the spaces between text and percentage */
    int i;
    for (i = 0; i < (int) cbar->text_bar_gap; ++i)
        putc(' ', stdout);
    /* Print percentage, % and left bar border */
    printf("%3.0f%% %c", ((float) cbar->progress / (float) cbar->max_value) * 100, cbar->bar.left_bar_boder);
    for (i = 0; i < (int) cbar->progress; ++i)
    {
        /* Only print if 1 charater in real is == to one in the bar */
        chars += chars_per_iter;
        while (chars >= 1)
        {
            putc(cbar->bar.indicator, stdout);
            chars--;
            chars_printed++;
        }
    }

    /* Print the head of the progress bar or the final indicator */
    if (cbar->progress < cbar->max_value)
        putc(cbar->bar.head, stdout);
    else
        for (;chars_printed < bar_width; chars_printed++)
            putc(cbar->bar.indicator, stdout);

    /* Print spaces between the head and the right bar border */
    for (i = 0; i < bar_width - (chars_printed + 1); ++i)
        putc(cbar->bar.unfinished, stdout);
    putc(cbar->bar.right_bar_border, stdout);

    /* ETA goes here */
    if (cbar->eta != 0)
    {
        if (cbar->progress == 0)
            printf(" 0h 0m 0s");
        else
        {
            double time_difference = difftime(time(NULL), cbar->ETA_START);
            double max_time = cbar->max_value * time_difference / cbar->progress;
            long time_prediction = (max_time - time_difference);
            int hours = time_prediction / 3600;
            time_prediction %= 3600;
            int min = time_prediction / 60;
            time_prediction %= 60;
            int sec = time_prediction;

            printf("%02dh %02dm %02ds", hours, min, sec);
        }
    }

    fflush(stdout);

    return 0;
}

void complex_bar_set_width(complex_progress_bar *cbar, unsigned int width)
{

    cbar->term_width = width;

}
void complex_bar_set_text(complex_progress_bar *cbar, char *format, ...)
{

    va_list ap;
    unsigned int width = get_term_width();
    cbar->text = realloc(cbar->text, width + 1);
    va_start(ap, format);
    vsnprintf(cbar->text, width, format, ap);
    va_end(ap);
}
int complex_bar_get_progress(complex_progress_bar *cbar)
{

    return cbar->progress;

}
void complex_bar_destroy(complex_progress_bar *cbar)
{
    free(cbar->text);
    free(cbar);

}

/* Here ends the part of complex progress bar */

void *create_shared_memory(size_t size) {

    /* Make shared memory readable and writeable */
    int protection = PROT_READ | PROT_WRITE;
    /* Make shared memory only visible to its children */
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    /* Return pointer to shared memory */
    return mmap(NULL, size, protection, visibility, -1, 0);

}
