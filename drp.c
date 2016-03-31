#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

DIR * dir;
struct dirent * de;
struct stat statbuf;
int status, i;

int main(int argc, char *argv[])
{
  dir = opendir(argv[1]);
  for (i = 0; i < 100; i++)
  {
    de = readdir(dir);

    printf("%s", de->d_name);

    stat(de->d_name, &statbuf);
 /* printf("%d\n",status); */
  if (S_ISDIR(statbuf.st_mode)){
    printf("    Yes\n");
  } else {
    printf("	No\n");
  }
  }
  closedir(dir);
  return 0;


}
