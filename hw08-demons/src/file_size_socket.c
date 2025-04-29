#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "file_size_socket.h"
#include "config.h"
#include "error_codes.h"
#include "file_size.h"

static int send_response(int sd);

int listen_file()
{
  int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    return OPEN_SOCKET_ERROR;
  }

  struct sockaddr_un server;
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, SOCKET_NAME);
  if (bind(sock_fd, (struct sockaddr*) &server, sizeof(struct sockaddr_un))) {
    return STREAM_BINDING_ERROR;
  }
  listen(sock_fd, MAX_PENDING_CONNECTIONS);

  int bytes_read;
  char buf[1024];
  for (;;) {
    int msg_fd = accept(sock_fd, 0, 0);
    do {
      bzero(buf, sizeof(buf));
      bytes_read = read(msg_fd , buf, 1024);
      int code = send_response(msg_fd);
      if (code != 0) {
        close(msg_fd);
        return code;
      }
    } while (bytes_read > 0);
    close(msg_fd);
  }

  close(sock_fd);
  unlink(SOCKET_NAME);

  return 0;
}

static int send_response(int msg_fd)
{
  char path[PATH_MAX];
  int code = get_filepath(path);
  if (code == PARAM_NOT_FOUND_ERROR) {
    return PARAM_NOT_FOUND_ERROR;
  }

  long file_size;
  code = get_file_size(path, &file_size);
  if (code == FILE_NOT_FOUND_ERROR) {
    return FILE_NOT_FOUND_ERROR;
  }

  char size[20];
  sprintf(size, "%ld\n", file_size);
  send(msg_fd, size, strlen(size), 0);

  return 0;
}
