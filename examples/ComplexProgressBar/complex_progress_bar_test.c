/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

	complex_progress_bar *cbar = complex_bar_create();
	complex_bar_set_bar_attributes(cbar, 0, "A sample text", '|', '=', '>', '-', '|', 0, 5);

	int i;
	for (i = 0; i < 101; ++i)
	{
		complex_bar_set_progress(cbar, i);
		complex_bar_print(cbar);
		usleep(100000);
	}
	/* End the bar with a new line */
	putc('\n', stdout);

	/* Destroy the bar */
	complex_bar_destroy(cbar);

	return 0;
}
