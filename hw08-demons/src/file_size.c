#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "file_size.h"
#include "error_codes.h"

static long get_size(const char* filepath);

int get_file_size(const char *filepath, long* result_size)
{
  if (access(filepath, F_OK) != 0) {
    return FILE_NOT_FOUND_ERROR;
  }
  *result_size = get_size(filepath);

  return 0;
}

static long get_size(const char* filepath)
{
  struct stat stats;
  stat(filepath, &stats);
  long size = stats.st_size;

  if (!S_ISDIR(stats.st_mode)) {
    return size;
  }

  DIR* dir = opendir(filepath);
  struct dirent* dir_entry;
  while((dir_entry = readdir(dir))) {
    if (!strcmp(".", dir_entry->d_name)
        || !strcmp("..", dir_entry->d_name)) {
      continue;
    }
    char entry_path[PATH_MAX];
    sprintf(entry_path, "%s/%s", filepath, dir_entry->d_name);
    size += get_size(entry_path);
  }
  closedir(dir);

  return size;
}
