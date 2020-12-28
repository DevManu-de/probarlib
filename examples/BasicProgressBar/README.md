# Explanation of functions

## Short description
The progress bar diplays a text, percentage and a bar that shows its progress. More information is on the bottom of this document.

## basic_bar_create()
>
> Return value
> it returns a pointer to a progress bar structure. NULL on memory allocation fail.

## basic_bar_set_bar_attributes()
>
> 1. Argument
> is the pointer to the progress bar.
>
> 2. Argument
> is the text in front of the progress bar.
>
> Return value
> is 0 on success. -1 on `strdup()` fail.

## basic_bar_set_progress()
> 
> 1. Argument
> is the pointer to the progress bar.
> 
> 2. Argument
> is the percentage of completion as an unsigned integer.
> 
> Return value
> NONE (void)

## basic_bar_print()
> 
> 1. Argument
> is the bar to print.
> 
> Return value
> is 0 on succes.

## basic_bar_set_text()
> 
> 1. Argument
> is the bar.
> 
> 2. Argument
> is the new text.
> 
> Return value
> NULL (void)

## basic_bar_get_progress()
> 
> 1. Argument
> is the bar.
> 
> Return value
> the percentage of the bar.

## basic_bar_destroy()
> 
> 1. Argument
> is the bar.
> 
> Return value
> NONE (void)

## Usage

A example similar to the one in `basic_progress_bar_test.c`

```     
/* Create bar */
     basic_progress_bar *bar = basic_bar_create();
     /* Set A sample text as text for the bar */
     basic_bar_set_bar_attributes(bar, "A sample text");

     int i;
     for (i = 0; i < 101; ++i)
     {
         /* This sets the progress of the bar but doesnt print it */
         basic_bar_set_progress(bar, i);
         /* Prints the bar to stdout and changes its size if terminal is resized */
         basic_bar_print(bar);
         /* Just a sleep */
         usleep(100000);
     }
     /* End the bar with a new line */
     putc('\n', stdout);

     /* Destroy the bar */
     basic_bar_destroy(bar);
```
Output:
`Sample text          0% [                               ]`

see the `basic_progress_bar_test.c` for more code.

To run the sample code:
`make run`
