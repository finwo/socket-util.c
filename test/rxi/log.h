#ifndef RXI_LOG_H
#define RXI_LOG_H

#include <stdio.h>

#define log_error(fmt, ...) fprintf(stderr, "ERROR: " fmt "\n", ##__VA_ARGS__)
#define log_warn(fmt, ...) fprintf(stderr, "WARN: " fmt "\n", ##__VA_ARGS__)
#define log_info(fmt, ...) fprintf(stderr, "INFO: " fmt "\n", ##__VA_ARGS__)
#define log_debug(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)

#endif
