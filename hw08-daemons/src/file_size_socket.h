#ifndef FILE_SIZE_SOCKET_H
#define FILE_SIZE_SOCKET_H

#define SOCKET_NAME "file-size.socket"
#define MAX_PENDING_CONNECTIONS 5

int listen_file(const char* path);

#endif
