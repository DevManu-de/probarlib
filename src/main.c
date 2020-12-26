/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include "probar.h"
#include <unistd.h>

int main(){

	/* Create bar with a total row size of 210, indicator = # and a text */
	progressbar *bar = bar_create(210, '#', "This is a sample text");

	int i;
	for (i = 0; i < 101; i++)
	{
		/* This demonstrates the ability to resize the bar when terminal changes */
		if (i == 50)
			bar_set_width(bar, 105);

		/* This demonstrates the ability to resize the bar when terminal changes */
		if (i == 75)
		{
			bar_set_text(bar, "text");
			bar_set_width(bar, 210);
		}
		/* This sets the progress of the bar but doesnt print it */
		bar_set_progress(bar, i);
		/* Prints the bar to stdout but doesnt change its size if terminal is resized */
		bar_print(bar);
		/* Just a sleep */
		usleep(100000);
	}
	/* End the bar with a new line */
	putc('\n', stdout);

	/* Destroy the bar */
	bar_destroy(bar);

	return 0;
}
