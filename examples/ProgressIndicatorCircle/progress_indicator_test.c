/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

    progress_indicator *indicator = indicator_create(50, "A sample text", 40);
    indicator_start(indicator);
    sleep(1);
    indicator_set_text(indicator, "Progress 1");
    sleep(3);
    indicator_set_text(indicator, "Progress 2 is doing shit");
    sleep(2);
    indicator_set_text(indicator, "Progress 3");
    sleep(1);
    indicator_set_text(indicator, "P");
    sleep(5);
    indicator_set_text(indicator, "Progress 5");
    indicator_stop(indicator);
    indicator_destroy(indicator);

    return 0;
}
