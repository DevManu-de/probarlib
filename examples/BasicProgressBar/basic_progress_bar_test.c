/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

	/* Create bar */
	basic_progress_bar *bar = basic_bar_create();
	/* Set A sample text as text for the bar */
	basic_bar_set_bar_attributes(bar, "A sample text");

	int i;
	for (i = 0; i < 101; ++i)
	{
		/* This only demonstrates the ability to change the text during execution */
		if (i == 75)
			basic_bar_set_text(bar, "text");

		/* This sets the progress of the bar but doesnt print it */
		basic_bar_set_progress(bar, i);
		/* Print bar to stdout. Will react to terminal width changes */
		basic_bar_print(bar);
		/* Just a sleep */
		usleep(100000);
	}
	/* End the bar with a new line */
	putc('\n', stdout);

	/* Destroy the bar */
	basic_bar_destroy(bar);

	return 0;
}
