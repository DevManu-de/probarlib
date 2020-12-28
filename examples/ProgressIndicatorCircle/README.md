# Short description
The progress indicator circle prints a text and a rotating aimantion. More information is on the bottom of this document.

# Explanation of functions

## indicator_create()
> 
> 1. Argument 
> is the width of the terminal in characters. (How many characters fit in one row)
> This must be larger than the text
> 
> 2. Argument
> is the text that is diplayed in front of the circle.
> 
> 3. Argument
> is the max length that the text will ever get.
>
> Return value
> it returns a pointer to a progress indicator structure. NULL on memory allocation fail.

## indicator_start()
>
> 1. Argument
> is the progress indicator
>
> Return value
> is 0 on successful creation of the child. -1 if child creation failed.

## indicator_set_width()
> 
> 1. Argument
> is the progress indicator.
> 
> 2. Argument
> is the width of the terminal in characters. (How many characters fit in one row)
> 
> Return value
> NONE (void)

## indicator_set_text()
> 
> 1. Argument
> is the progress indicator.
> 
> 2. Argument
> is the new text.
> 
> Return value
> NULL (void)

## indicator_stop()
>
> 1. Argument
> is the progress indicator.
>
> Return value
> is 1 if child killing was succesful. 0 if child killing was unsuccessful.

## indicator_destroy()
> 
> 1. Argument
> is the progress indicator.
> 
> Return value
> NONE (void)

## Usage

A example similar to the one in `progress_indicator_test.c`

```
progress_indicator *indicator = indicator_create(50, "A sample text", 20);

/* Start the progress indicator */
indicator_start(indicator);

/* Set a new text */
indicator_set_text(indicator, "Progress 1");

/* Change the width of the row */
indicator_set_width(indicator, 210);

/* Stop the progress indicator but not dealloc it */
indicator_stop(indicator);

/* Deallocs the progress indicator */
indicator_destroy(indicator);
```
Output:
`A sample text          \`

see the `progress_indicator_test.c` for more code.
IMPORTANT: everything that needs to be printed after indicator_start() was called must be done with indicator_set_text().

To run the sample code:
`make run`
