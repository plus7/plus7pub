#include <limits.h>
#include <unistd.h>

int getpathmax()
{
#ifdef PATH_MAX
  int path_max = PATH_MAX;
#else
  int path_max = pathconf(path, _PC_PATH_MAX);
  if (path_max <= 0)
         path_max = 4096;
#endif
	return path_max;
}
