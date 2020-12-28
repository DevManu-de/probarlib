# Explanation of functions

## Short description
The progress bar diplays a text, percentage and a bar that shows its progress. More information is on the bottom of this document.

## complex_bar_create()
>
> Return value
> it returns a pointer to a progress bar structure.

## complex_bar_set_progress()
> 
> 1. Argument
> is the pointer to the progress bar.
> 
> 2. Argument
> is the percentage of completion as an unsigned integer.
> 
> Return value
> NONE (void)

## complex_bar_print()
> 
> 1. Argument
> is the bar to print.
> 
> Return value
> is 0 on succes.

## complex_bar_set_width()
> 
> 1. Argument
> is the bar.
> 
> 2. Argument
> is the width of the terminal in characters. (How many characters fit in one row)
> 
> Return value
> 0 on success but -1 if term_width is not large enough.

## complex_bar_set_text()
> 
> 1. Argument
> is the bar.
> 
> 2. Argument
> is the new text.
> 
> Return value
> NULL (void)

## complex_bar_get_progress()
> 
> 1. Argument
> is the bar.
> 
> Return value
> the percentage of the bar.

## complex_bar_destroy()
> 
> 1. Argument
> is the bar.
> 
> Return value
> NONE (void)

## Usage

A example similar to the one in `complex_progress_bar_test.c`

```
int screen_width = 210;

progress *bar = complex_bar_create();
/* set cbar, 0 = automatic resizeing, text, left bar border, indicator, head, char between head and right bar border, right bar border, if ETA should be calculated, space between text and percentage */
complex_bar_set_bar_attributes(bar, 0, "Text", '(', '$', '>', '=', ' )', 0, 1);

int i;
for (i = 0; i < 101; ++i)
{
    /* Do stuff, set progress and print bar */
    complex_bar_set_progress(bar, i);
    complex_bar_print(bar);
}

/* This ends the bar */
putc('\n', stdout);

/* Destroys the bar */
complex_bar_destroy(bar);
```
Output:
`Text 90% ($$$$$$$$$> )`

see the `complex_progress_bar_test.c` for more code.

To run the sample code:
`make run`
