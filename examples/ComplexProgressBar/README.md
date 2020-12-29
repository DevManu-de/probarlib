# Explanation of functions

## Short description
The progress bar diplays a text, percentage and a bar that shows its progress. More information is on the bottom of this document.

## complex_bar_create()
>
> Return value
> it returns a pointer to a progress bar structure.

## complex_bar_set_bar_attributes()
>
>
> 1. Argument
> is the bar.
>
> 2. Argument
> is the width of the entire bar. 0 means dynamically resize complex_bar_set_width() is never required then.
>
> 3. Argument
> is the text to be displayed in front of the bar.
>
> 4. Argument
> is the left bar border
>
> 5. Argument
> is the indicator that shows the progress
>
> 6. Argument
> is the head in front of the indicator
>
> 7. Argument
> is the character between the head and the right bar border
>
> 8. Argument
> is the right bar border
>
> 9. Argument
> is ETA. 1 means calculate ETA. 0 means dont calculate ETA.
>
> 10. Argument
> is the space between text and the percentage
>
> 11. Argument
> is the max value the bar can get.
>
> Return value
> 0 on success, -1 on strdup fail.

## complex_bar_start_eta()
>
> 1. Argument
> is the bar.
>
> Return value
> NONE (void)

## complex_bar_get_duration()
>
> 1. Argument
> is the bar.
>
> Return value
> is the seconds (double) from complex_bar_start_eta() to 100% of the bar.
> The precision is +1 seconds on max_value == 1000

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
progress *bar = complex_bar_create();
/* set cbar, 0 = automatic resizeing, text, left bar border, indicator, head, char between head and right bar border, right bar border, if ETA should be calculated, space between text and percentage, max value */
complex_bar_set_bar_attributes(bar, 0, "Text", '(', '$', '>', '=', ' )', 0, 1, 100);

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
`Text 90% ($$$$$$$$$>===)`

see the `complex_progress_bar_test.c` for more code.

To run the sample code:
`make run`
