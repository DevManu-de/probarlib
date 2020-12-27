/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

    progress_indicator *indicator = indicator_create(210, "A sample text");
    indicator_start(indicator);
    sleep(1);
    indicator_set_text(indicator, "Progress 1");
    sleep(1);
    indicator_set_text(indicator, "Progress 2");
    sleep(1);
    indicator_set_text(indicator, "Progress 3");
    sleep(1);
    indicator_set_text(indicator, "Progress 4");
    sleep(1);
    indicator_set_text(indicator, "Progress 5");
    indicator_stop(indicator);
    indicator_destroy(indicator);

    return 0;
}
