/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "probar.h"

int main(){

    progress_indicator *indicator = indicator_create(210, "A sample text");
    indicator_start(indicator);
    indicator_stop(indicator);
    indicator_destroy(indicator);

    return 0;
}
