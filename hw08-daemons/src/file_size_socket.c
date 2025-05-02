#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "file_size_socket.h"
#include "error_codes.h"
#include "file_size.h"

static volatile int keep_running = 1;

static void send_response(const char* path, int sd);
static void sigint_handler();

int listen_file(const char* path)
{
  int sock_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
  signal(SIGINT, sigint_handler);
  while (keep_running) {
    int msg_fd = accept(sock_fd, 0, 0);
    if (msg_fd < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      usleep(1000);
    } else {
      send_response(path, msg_fd);
      close(msg_fd);
    }
  }

  close(sock_fd);
  unlink(SOCKET_NAME);

  return 0;
}

static void send_response(const char* path, int msg_fd)
{
  long file_size;
  int code = get_file_size(path, &file_size);
  if (code == FILE_NOT_FOUND_ERROR) {
    char* message = "file not found\n";
    send(msg_fd, message, strlen(message), 0);
    return;
  }

  char size[20];
  sprintf(size, "%ld\n", file_size);
  send(msg_fd, size, strlen(size), 0);
}

static void sigint_handler()
{
  keep_running = 0;
}
