#include "zip_util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static bool find_eo_dir(FILE* file, eo_central_dir* dir);

zip_summary read_zip(FILE* file)
{
  zip_summary zs;
  zs.has_error = false;
  eo_central_dir* ecd = malloc(sizeof(eo_central_dir));
  bool has_ecd = find_eo_dir(file, ecd);

  printf("entries: %d\n", ecd->num_entries);
  printf("sig: 0x%08x\n", ecd->signature);
  printf("offset from ecd: %d\n", ecd->central_directory_offset);

  if (!has_ecd) {
    free(ecd);
    zs.is_zip = false;
    zs.filenames = "";
    return zs;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

//  for (long i = 0; i < file_size;) {
//    uint32_t sig;
//    fread(&sig, sizeof(uint32_t), 1, file);
//    if (sig == GLOBAL_FILE_HEADER_SIGNATURE) {
//      printf("file header offset %ld\n", ftell(file) - 4);
//      fseek(file, -4, SEEK_CUR);
//      break;
//    }
//    fseek(file, ++i, SEEK_SET);
//  }

  fseek(file, ecd->central_directory_offset, SEEK_SET);

  for (int i = 0; i < ecd->num_entries; i++) {
    global_file_header gfh;
    fread(&gfh, sizeof(global_file_header), 1, file);

    if (gfh.signature == GLOBAL_FILE_HEADER_SIGNATURE) {
      char filename[gfh.filename_length + 1];
      filename[gfh.filename_length] = '\0';
      fread(filename, gfh.filename_length, 1, file);
      printf("filename: %s\n", filename);

      fseek(file, gfh.extra_field_length + gfh.file_comment_length, SEEK_CUR);
    } else {
      printf("ERROR\n");
    }
  }

  zs.is_zip = true;
  zs.filenames = "";

  return zs;
}

static bool find_eo_dir(FILE* file, eo_central_dir* dir)
{
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, file_size, SEEK_SET);

  while (file_size > 0) {
    fread(dir, sizeof(eo_central_dir), 1, file);
    if (dir->signature == EO_CENTRAL_DIR_SIGNATURE) {
      return true;
    }

    fseek(file, --file_size, SEEK_SET);
  }

  return false;
}
