#include "get_next_line.h"

int  main()
{

	char* fileName = "test.txt";

	int fd = open(fileName, O_RDWR);

	get_next_line(fd);

	return 0;
}
