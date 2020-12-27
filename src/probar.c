/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "probar.h"

progress_bar *bar_create(unsigned int term_width, char indicator, char *text)
{
    progress_bar *bar = malloc(sizeof(progress_bar));
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
