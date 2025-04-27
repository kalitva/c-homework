#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "file_size.h"
#include "error_codes.h"

static int get_size(char* path);

int get_file_size(char *path, int* result_size)
{
  if (access(path, F_OK) != 0) {
    return FILE_NOT_FOUND_ERROR;
  }
  *result_size = get_size(path);
  return 0;
}

static int get_size(char* path)
{
  struct stat s;
  stat(path, &s);
  int size = s.st_size;

  if (!S_ISDIR(s.st_mode)) {
    return size;
  }

  DIR* dir = opendir(path);
  struct dirent* dir_entry;
  while((dir_entry = readdir(dir))) {
    if (!strcmp(".", dir_entry->d_name)
        || !strcmp("..", dir_entry->d_name)) {
      continue;
    }
    char entry_path[PATH_MAX];
    sprintf(entry_path, "%s/%s", path, dir_entry->d_name);
    size += get_size(entry_path);
  }
  closedir(dir);

  return size;
}
