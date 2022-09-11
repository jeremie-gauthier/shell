#include <stdbool.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

bool can_readf(const int fd)
{
	if (read(fd, NULL, 0) < 0)
		return false;
	return true;
}
