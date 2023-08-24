#include "get_next_line_bonus.h"
#include <stdio.h>

int main(void)
{
	char *temp;

	temp = get_next_line(0);
	printf("%s\n", temp);
	free(temp);
	return 1;
}