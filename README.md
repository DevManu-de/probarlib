# probarlib
probarlib is a library that allows you to create a simple progress bar in the terminal.
You can customize the text in front of the bar the bar filling character (indicator) and the size of the entire bar.
If you want to use it in your own project you need to know the width of the terminal or enter a static width.
I chose not to get the terminal width dynamically because it could cause some unnecessary calculation for example:
You already have a project that collects the width of the terminal so it is unnecessary to collect it again.
Another example:
You want the bar only to take half of the terminal.
And dynamically collecting the terminal size would result in a dependency like ncurses.

BTW probarlib is C89 compatible

If any questions come up dont hesitate to open an issue or if you want to contribute just open a pull request.

# Description
This is a library that allows you to diplay a progress bar.

# Explanation of functions

## bar_create()
>
> 1. Argument 
>is the width of the terminal in characters. (How many characters fit in one row)
>IMPORTANT this cant be smaller than `strlen(text) + 17` because if it is then the bar itself would have a negative width.
>The 17 from the calculation comes from the 10 spaces between the text and 3 for the percentage and the other 4 from the %, a space and the [] around the bar.
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

A example similar to the one in `src/main.c`

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

see the `src/main.c` for more code
in the `src/main.c` the bar resizes at 50% and leaves some `#` on the screen but this only occurs if you dont actually resize the terminal.
In reallity this wont happen and its only in the code to show the ability to resize the bar.
