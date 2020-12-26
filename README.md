# probarlib

# Description
This is a library that allows you to diplay a progress bar.

# Explanation of functions

## bar_create()
>
> 1. Argument 
>is the width of the terminal in characters. (How many characters fit in one row)
>IMPORTANT this cant be smaller than `strlen(text) + 17` because if it is then the bar itself would have a negative width.
>The 17 from the calculation comes from the 10 spaces between the text and 3 for the percentage and the other 4 from the %, a space and the [] >around the bar.
>
> 2. Argument
>is the indicator, this char shows the progress. (Example: [#########        ] The # is the indicator in this bar example)
>
> 3. Argument
>is the text that is diplayed in front of the bar.
>
> Return value
>it returns a pointer to a progress bar structure.

## bar_set_progress()
>
> 1. Argument
>is the pointer to the progress bar.
>
> 2. Argument
>is the percentage of completion as an unsigned integer.
>
> Return value
>NONE (void)

## bar_print()
>
> 1. Argument
>is the bar to print.
>
> Return value
>is 0 on succes.
>
> bar_set_width
>
> 1. Argument
>is the bar.
>
> 2. Argument
>is the width of the terminal in characters. (How many characters fit in one row)
>
> Return value
>0 on success but -1 if term_width is not large enough.

## bar_set_text()
>
> 1. Argument
>is the bar.
>
> 2. Argument
>is the new text.
>
> Return value
>NULL (void)

## bar_get_progress()
>
> 1. Argument
>is the bar.
>
> Return value
>the percentage of the bar.

## bar_destroy()
>
> 1. Argument
>is the bar.
>
> Return value
>NONE (void)

## Usage
see the src/main.c
