/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

    /* Create a progress indicator with a width of 50, a text A sample text and a max text width of 40 */
    progress_indicator *indicator = indicator_create(50, "A sample text", 40);
    /* Start the progress indicator */
    indicator_start(indicator);
    /* Everything that should be printed to stdout must be done with
     * indicator_set_text() */
    sleep(1);
    /* The circle will keep spinning even is main thread is busy */
    indicator_set_text(indicator, "Progress 1");
    sleep(3);
    indicator_set_text(indicator, "Progress 2 is doing smth");
    sleep(2);
    indicator_set_width(indicator, 210);
    indicator_set_text(indicator, "Progress 3");
    sleep(1);
    indicator_set_text(indicator, "Prog");
    sleep(5);
    indicator_set_text(indicator, "Progress 5");
    /* Stop the spinning of the circle */
    indicator_stop(indicator);
    /* Now you can normally print to stdout with functions like puts */
    /* Free the memory of indicator */
	indicator_destroy(indicator);

    return 0;
}
