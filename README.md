# socket-util

A C library for common socket utilities including TCP/UDP/Unix socket creation and sockaddr manipulation.

## Installation

This library can be installed using the [dep](https://github.com/finwo/dep) package manager:

```bash
dep add finwo/socket-util
```

## Usage

```c
#include "socket-util.h"

int *fds = tcp_listen(":8080", NULL, NULL);
if (fds) {
    // fds[0] = count, fds[1+] = socket fds
    for (int i = 1; i <= fds[0]; i++) {
        printf("Listening on fd %d\n", fds[i]);
    }
    free(fds);
}
```

## Design Pattern: Config with Defaults

The `tcp_listen` and `udp_recv` functions are designed to read addresses from config files while providing programmatic fallback defaults:

```c
int *fds = tcp_listen(config_address, default_host, default_port);
```

- **First argument** (`addr`): Read from config file - can be empty/NULL
- **Second argument** (`default_host`): Hardcoded fallback host
- **Third argument** (`default_port`): Hardcoded fallback port

This allows flexible configuration:

```c
// Config provides ":8080" -> binds to 0.0.0.0:8080
int *fds = tcp_listen(":8080", NULL, NULL);

// Config provides "" (empty) -> uses hardcoded defaults
int *fds = tcp_listen("", "192.168.1.100", "5060");

// Config provides ":0" -> binds to random port, caller must detect actual port
int *fds = tcp_listen(":0", NULL, "0");
```

## Features

### TCP Listening

```c
// Simple: port from config, no defaults
int *fds = tcp_listen(":8080", NULL, NULL);

// Config-driven with defaults
int *fds = tcp_listen(config->sip_host, "0.0.0.0", "5060");

// Dual-stack (IPv4 + IPv6)
int *fds = tcp_listen(":5060", NULL, NULL);

// IPv4 only
int *fds = tcp_listen("0.0.0.0:5060", NULL, NULL);

// IPv6 only
int *fds = tcp_listen("[::]:5060", NULL, NULL);
```

### UDP Receiving

```c
// Simple: port from config
int *fds = udp_recv(":5060", NULL, NULL);

// With defaults
int *fds = udp_recv(config->rtp_host, "0.0.0.0", "10000");
```

### Unix Domain Sockets

```c
// Stream socket
int *fds = unix_listen("/run/mydaemon.sock", SOCK_STREAM, NULL);

// With ownership
int *fds = unix_listen("/run/mydaemon.sock", SOCK_STREAM, "daemonuser");

// Datagram socket with group
int *fds = unix_listen("/run/mydaemon.sock", SOCK_DGRAM, "daemonuser:daemogroup");
```

### Socket Address Conversion

```c
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
inet_pton(AF_INET, "192.168.1.1", &addr.sin_addr);

char buf[INET6_ADDRSTRLEN + 8];
sockaddr_to_string((struct sockaddr *)&addr, buf, sizeof(buf));
// buf = "192.168.1.1:8080"
```

### String to Socket Address

```c
struct sockaddr_storage addr;
int result = string_to_sockaddr("192.168.1.1:8080", &addr);
// result = 0 on success, -1 on error

result = string_to_sockaddr("[::1]:3000", &addr);
// For IPv6, wrap address in brackets
```

### Compare Socket Addresses

```c
struct sockaddr_in a, b;
a.sin_family = AF_INET;
b.sin_family = AF_INET;
// ... set addresses ...

if (sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b)) {
    // Addresses are equal
}
```

### Merge File Descriptor Arrays

```c
int *arr1 = malloc(sizeof(int) * 3);
arr1[0] = 2;
arr1[1] = 5;
arr1[2] = 10;

int *arr2 = malloc(sizeof(int) * 2);
arr2[0] = 1;
arr2[1] = 3;

int *arrays[] = { arr1, arr2 };
int *merged = merge_fd_arrays(arrays, 2);
// merged[0] = 3, merged[1] = 5, merged[2] = 10, merged[3] = 3
// Note: original arrays are freed
```

### Set Non-blocking

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
set_socket_nonblocking(fd, 1);  // Set non-blocking
set_socket_nonblocking(fd, 0);  // Set blocking
```

## Address Format

The address parsing supports:

- Port only: `:8080`, `8080` (uses defaults for host)
- IPv4: `192.168.1.1:8080`
- IPv6: `[::1]:8080`, `[2001:db8::1]:443`
- With defaults: `8080` with default host `0.0.0.0`

## Return Value Conventions

Functions returning `int *` (arrays):
- Returns `NULL` on error
- Index 0 contains the count
- Indices 1+ contain the values
- Caller is responsible for freeing the array

Functions returning `int`:
- Returns 0 on success
- Returns -1 on error

## License

Copyright (c) 2026 finwo. See LICENSE.md for details.
