#ifndef ZIP_UTIL_H
#define ZIP_UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#pragma pack()

#define EO_CENTRAL_DIR_SIGNATURE 0x06054b50

typedef struct {
    int32_t signature; // 0x06054b50
    unsigned short disk_number;
    unsigned short central_directory_disk_number;
    unsigned short num_entries_this_disk;
    unsigned short num_entries;
    int32_t central_directorySize;
    int32_t central_directory_offset;
    unsigned short zip_comment_length;
    // Followed by .ZIP file comment (variable size)
} eo_central_dir;

bool is_zipfile(FILE* file);
char* list_zipfiles(FILE* file);

#endif
