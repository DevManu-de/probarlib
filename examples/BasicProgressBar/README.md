# Explanation of functions

## Short description
The progress bar diplays a text, percentage and a bar that shows its progress. More information is on the bottom of this document.

## bar_create()
> 
> 1. Argument 
> is the width of the terminal in characters. (How many characters fit in one row)
> IMPORTANT this cant be smaller than `strlen(text) + 17` because if it is then the bar itself would have a negative width.
> The 17 from the calculation comes from the 10 spaces between the text and 3 for the percentage and the other 4 from the %, a space and the [] around the bar.
> 
> 2. Argument
> is the indicator, this char shows the progress. (Example: [#######        ] The # is the indicator in this bar example)
> 
> 3. Argument
> is the text that is diplayed in front of the bar.
> 
> Return value
> it returns a pointer to a progress bar structure.

## bar_set_progress()
> 
> 1. Argument
> is the pointer to the progress bar.
> 
> 2. Argument
> is the percentage of completion as an unsigned integer.
> 
> Return value
> NONE (void)

## bar_print()
> 
> 1. Argument
> is the bar to print.
> 
> Return value
> is 0 on succes.

## bar_set_width()
> 
> 1. Argument
> is the bar.
> 
> 2. Argument
> is the width of the terminal in characters. (How many characters fit in one row)
> 
> Return value
> 0 on success but -1 if term_width is not large enough.

## bar_set_text()
> 
> 1. Argument
> is the bar.
> 
> 2. Argument
> is the new text.
> 
> Return value
> NULL (void)

## bar_get_progress()
> 
> 1. Argument
> is the bar.
> 
> Return value
> the percentage of the bar.

## bar_destroy()
> 
> 1. Argument
> is the bar.
> 
> Return value
> NONE (void)

## Usage

A example similar to the one in `progress_bar_test.c`

```
int screen_width = 210;

progress *bar = bar_create(screen_width, '#', "Sample text");

int i;
for (i = 0; i < 101; ++i)
{
    /* Do stuff and update screen_width to be able to recognize terminal size changes */
    bar_set_width(bar, screen_width);
    bar_set_progress(bar, i);
    bar_print(bar);
}

/* This ends the bar */
putc('\n', stdout);

/* Destroys the bar */
bar_destroy(bar);
```
Output:
`Sample text          0% [                               ]`

see the `progress_bar_test.c` for more code.
In the `progress_bar_test.c` the bar resizes at 50% and leaves some `#` on the screen but this only occurs if you dont actually resize the terminal.
In reallity this wont happen and its only in the code to show the ability to resize the bar.
