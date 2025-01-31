#include "zip_util.h"
#include <stdlib.h>

static void find_eocd(FILE* file, end_of_central_dir* dir, uint32_t* eocd_offset);
static void print_filenames(FILE* file, uint32_t cd_offset, unsigned short num_entries);

void print_zip_files(FILE* file)
{
  end_of_central_dir* eocd = malloc(sizeof(end_of_central_dir));
  uint32_t eocd_offset;
  find_eocd(file, eocd, &eocd_offset);
  uint32_t cd_offset = eocd_offset - eocd->central_directory_size;
  print_filenames(file, cd_offset, eocd->num_entries);
  free(eocd);
}

bool is_zipfile(FILE* file)
{
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, file_size, SEEK_SET);

  while (file_size > 0) {
    uint32_t sig;
    fread(&sig, sizeof(uint32_t), 1, file);
    if (sig == EO_CENTRAL_DIR_SIGNATURE) {
      return true;
    }
    fseek(file, --file_size, SEEK_SET);
  }

  return false;
}

static void print_filenames(FILE* file, uint32_t cd_offset, unsigned short num_entries)
{
  fseek(file, cd_offset, SEEK_SET);
  for (int i = 0; i < num_entries; i++) {
    global_file_header gfh;
    fread(&gfh, sizeof(global_file_header), 1, file);

    if (gfh.signature != GLOBAL_FILE_HEADER_SIGNATURE) {
      printf("ERROR: file header signature not found\n");
      break;
    }

    char filename[gfh.filename_length + 1];
    filename[gfh.filename_length] = '\0';
    fread(filename, gfh.filename_length, 1, file);
    printf("%s\n", filename);

    fseek(file, gfh.extra_field_length + gfh.file_comment_length, SEEK_CUR);
  }
}

static void find_eocd(FILE* file, end_of_central_dir* eocd, uint32_t* eocd_offset)
{
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, file_size, SEEK_SET);

  while (file_size > 0) {
    fread(eocd, sizeof(end_of_central_dir), 1, file);
    if (eocd->signature == EO_CENTRAL_DIR_SIGNATURE) {
      *eocd_offset = ftell(file) - sizeof(end_of_central_dir);
      return;
    }

    fseek(file, --file_size, SEEK_SET);
  }
}
