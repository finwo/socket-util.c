#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

#include <sys/socket.h>

int set_socket_nonblocking(int fd, int nonblock);

int *tcp_listen(const char *addr, const char *default_host, const char *default_port);

int *udp_recv(const char *addr, const char *default_host, const char *default_port);

int *unix_listen(const char *path, int sock_type, const char *owner);

int *merge_fd_arrays(int **arrays, int count);

void sockaddr_to_string(const struct sockaddr *addr, char *buf, size_t buf_size);

int string_to_sockaddr(const char *str, struct sockaddr_storage *addr);

int sockaddr_equal(const struct sockaddr *a, const struct sockaddr *b);

#endif
