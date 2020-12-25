#include "probar.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

progressbar *create_bar(unsigned int term_width, char indicator, char *text)
{
    progressbar *bar = malloc(sizeof(progressbar));
    bar->indicator = indicator;
    bar->progress = 0;
    bar->term_width = term_width;
    bar->text = strdup(text);

    return bar;

}
void set_bar_progress(progressbar *bar, unsigned int progress)
{
    bar->progress = progress;

}

void set_bar_width(progressbar *bar, unsigned int term_width)
{
    bar->term_width = term_width;

}

int print_bar(progressbar *bar)
{
    unsigned int bar_width = bar->term_width - strlen(bar->text) - 17;
    float chars_per_iter = (float) bar_width / 100;
    float chars = 0.0;
    unsigned int chars_printed = 0;

    printf("\r%s          %3d%% [", bar->text, bar->progress);
    unsigned int i;
    for (i = 0; i < bar->progress; i++)
    {
        chars += chars_per_iter;
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

    for (i = 0; i < bar_width - chars_printed; i++)
    {
        putc(' ', stdout);
    }
    putc(']', stdout);
    fflush(stdout);
    return 0;

}

unsigned int get_progress(progressbar *bar)
{
    return bar->progress;
}

void destroy_bar(progressbar *bar)
{
    free(bar);
}
