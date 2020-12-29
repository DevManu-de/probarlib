/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

	/* Create new complex progress bar */
	complex_progress_bar *cbar = complex_bar_create();
	unsigned int max_value = 1000;
	/* set cbar, 0 = automatic resizeing, text, left bar border, indicator, head, char between head and right bar border, right bar border, if ETA should be calculated, space between text and percentage */
	complex_bar_set_bar_attributes(cbar, 0, "A sample text", '|', '=', '>', '-', '|', 1, 5, max_value);
	complex_bar_start_eta(cbar);
	/* The eta counter will have some jumps on the beginning but at about 25% the eta counter
	 * wont have great jumps. This is normal and caused by the predicition algorithim I use. */
	unsigned int i;
	for (i = 0; i <= max_value; ++i)
	{
		/* Set progress but doesnt print */
		complex_bar_set_progress(cbar, i);
		/* Print progress bar */
		complex_bar_print(cbar);
		usleep(100000);
	}
	/* End the bar with a new line */
	putc('\n', stdout);

	/* Get the time in seconds how long it took to go from 0% to 100% */
	printf("%f\n", complex_bar_get_duration(cbar));
	/* In this example it will return 100 sometimes 101 seconds because precision is about + 1 per 1000 iterations (== max_value) */

	/* Destroy the bar */
	complex_bar_destroy(cbar);

	return 0;
}
