#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "terminfo.h"

#include "terminfo_data.c"

#define TERMINFO_PATH "/tmp/terminfo"
#define TERMINFO_S_PATH TERMINFO_PATH"/s"
#define TERMINFO_S_FILE TERMINFO_S_PATH"/st-256color.gz"

void terminfo_set()
{
	int fd = -1;
	int len = sizeof(terminfo_data);

	terminfo_remove();
	setenv("TERMINFO", TERMINFO_PATH, 1);
	system("mkdir -p " TERMINFO_S_PATH);

	fd = creat(TERMINFO_S_FILE, 0644);
	if (fd < 0) goto err2;
	if (write(fd, terminfo_data, len) != len) goto err;
	close(fd);
	system("gunzip " TERMINFO_S_FILE);
	return;
err:
	close(fd);
err2:
	terminfo_remove();
	return;
}

void terminfo_remove()
{
	system("rm -rf " TERMINFO_PATH);
	unsetenv("TERMINFO");
}
