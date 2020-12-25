#include <stdio.h>
#include <stdlib.h>
#include "probar.h"
#include <unistd.h>

int main(int argc, const char *argv[]){

	progressbar *bar = create_bar(105, '#', "asldfjhksadflfkasdjfjshgf");

	int i;
	for (i = 0; i < 101; i++)
	{
		//if (i == 50)
		//	set_bar_width(bar, 105);

		//if (i == 75)
		//	set_bar_width(bar, 210);

		set_bar_progress(bar, i);
		print_bar(bar);
		usleep(100000);
	}
	putc('\n', stdout);

	destroy_bar(bar);

}
