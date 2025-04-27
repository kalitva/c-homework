#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "file_size_socket.h"

int listen_file(char *filename)
{
  int sock, msgsock, rval;
  struct sockaddr_un server;
  char buf[1024];

  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("opening stream socket");
    exit(1);
  }
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, SOCKET_NAME);
  if (bind(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un))) {
    perror("binding stream socket");
    exit(1);
  }
  printf("Socket has name %s\n", server.sun_path);
  listen(sock, 5);

  for (;;) {
    msgsock = accept(sock, 0, 0);
    if (msgsock == -1) {
      perror("accept");
      break;
    } else do {
      bzero(buf, sizeof(buf));
      if ((rval = read(msgsock, buf, 1024)) < 0) {
        perror("reading stream message");
      } else if (rval == 0) {
        printf("Ending connection\n");
      } else {
        send(msgsock, buf, strlen(buf), 0);
      }
    } while (rval > 0);
    close(msgsock);
  }

  close(sock);
  unlink(SOCKET_NAME);

  return 0;
}
