#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "src/config.h"
#include "src/error_codes.h"
#include "src/file_size_socket.h"

static void daemonize(struct config* config);

int main(int argc, char** argv)
{
  int code;
  char* config_path = argv[1];
  struct config config;
  code = create_config(config_path, &config);
  if (code == CONFIG_NOT_FOUND_ERROR) {
    printf("config file '%s' not found\n", config_path);
    return CONFIG_NOT_FOUND_ERROR;
  } else if (code == FILEPATH_PARAM_NOT_FOUND_ERROR) {
    printf("parameter filepath not found\n");
    return FILEPATH_PARAM_NOT_FOUND_ERROR;
  }

  if (config.demonized) {
    daemonize(&config);
  }

  code = listen_file(config.filepath);
  destroy_config(&config);

  if (code == STREAM_BINDING_ERROR) {
    printf("stream binding error\n");
    return STREAM_BINDING_ERROR;
  } else if (code == OPEN_SOCKET_ERROR) {
    printf("open socket error\n");
    return OPEN_SOCKET_ERROR;
  } else if (code == FILE_NOT_FOUND_ERROR) {
    printf("file not found\n");
    return FILE_NOT_FOUND_ERROR;
  }

  return 0;
}

static void daemonize(struct config* config)
{
  printf("starting service as a daemon\n");
  pid_t child;
  if ((child=fork()) < 0) {
    printf("error: failed fork\n");
    exit(FORK_FAILED_ERROR);
  }
  if (child > 0) {
    exit(EXIT_SUCCESS);
  }
  if (setsid() < 0) {
    printf("error: failed setsid\n");
    exit(SETID_FAILED_ERROR);
  }

  signal(SIGCHLD,SIG_IGN);
  signal(SIGHUP,SIG_IGN);

  if ((child = fork()) < 0) {
    printf("error: failed fork\n");
    exit(FORK_FAILED_ERROR);
  }
  if (child > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);
  chdir(config->homedir ? config->homedir : ".");

  char* logfile = config->logfile ? config->logfile : "server.log";
  freopen("/dev/null", "a+", stdin);
  freopen(logfile,"a+", stderr);
  freopen(logfile,"a+", stdout);
}
