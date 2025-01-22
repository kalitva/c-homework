#ifndef ZIP_UTIL_H
#define ZIP_UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define EO_CENTRAL_DIR_SIGNATURE 0x06054b50
#define LOCAL_FILE_HEADER_SIGNATURE 0x04034b50
#define GLOBAL_FILE_HEADER_SIGNATURE 0x02014b50

#pragma pack(push, 1)

typedef struct {
  uint32_t signature;
  unsigned short version;
  unsigned short flags;
  unsigned short compression_method;
  unsigned short last_modified_time;
  unsigned short last_modified_date;
  uint32_t crc_32;
  uint32_t compressed_size;
  uint32_t uncompressed_size;
  unsigned short filename_length;
  unsigned short extra_field_length;
} local_file_header;

typedef struct {
  uint32_t signature;
  unsigned short version;
  unsigned short version_to_extract;
  unsigned short flags;
  unsigned short compression_method;
  unsigned short last_modified_time;
  unsigned short last_modified_date;
  uint32_t crc_32;
  uint32_t compressed_size;
  uint32_t uncompressed_size;
  unsigned short filename_length;
  unsigned short extra_field_length;
  unsigned short file_comment_length;
  unsigned short disk_number_start;
  unsigned short internal_file_attributes;
  uint32_t external_file_attributes;
  uint32_t local_header_offset;
} global_file_header;

typedef struct {
  uint32_t signature;
  unsigned short disk_number;
  unsigned short central_directory_disk_number;
  unsigned short num_entries_this_disk;
  unsigned short num_entries;
  uint32_t central_directory_size;
  uint32_t central_directory_offset;
  unsigned short zip_comment_length;
} eo_central_dir;

typedef struct {
  bool is_zip;
  bool has_error;
  char* filenames;
} zip_summary;

#pragma pack(pop)

zip_summary read_zip(FILE* file);
#endif
