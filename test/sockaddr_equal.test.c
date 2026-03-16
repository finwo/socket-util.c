#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "socket-util.h"
#include "test.h"

void test_sockaddr_equal_ipv4_same() {
    struct sockaddr_in a, b;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &a.sin_addr);
    a.sin_port = htons(8080);

    b.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &b.sin_addr);
    b.sin_port = htons(8080);

    ASSERT("ipv4 same", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 1);
}

void test_sockaddr_equal_ipv4_different_ip() {
    struct sockaddr_in a, b;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &a.sin_addr);
    a.sin_port = htons(8080);

    b.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.2", &b.sin_addr);
    b.sin_port = htons(8080);

    ASSERT("ipv4 different ip", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 0);
}

void test_sockaddr_equal_ipv4_different_port() {
    struct sockaddr_in a, b;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &a.sin_addr);
    a.sin_port = htons(8080);

    b.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &b.sin_addr);
    b.sin_port = htons(8081);

    ASSERT("ipv4 different port", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 0);
}

void test_sockaddr_equal_ipv6_same() {
    struct sockaddr_in6 a, b;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &a.sin6_addr);
    a.sin6_port = htons(3000);

    b.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &b.sin6_addr);
    b.sin6_port = htons(3000);

    ASSERT("ipv6 same", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 1);
}

void test_sockaddr_equal_ipv6_different_ip() {
    struct sockaddr_in6 a, b;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &a.sin6_addr);
    a.sin6_port = htons(3000);

    b.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::2", &b.sin6_addr);
    b.sin6_port = htons(3000);

    ASSERT("ipv6 different ip", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 0);
}

void test_sockaddr_equal_different_family() {
    struct sockaddr_in a;
    struct sockaddr_in6 b;

    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));

    a.sin_family = AF_INET;
    b.sin6_family = AF_INET6;

    ASSERT("different family", sockaddr_equal((struct sockaddr *)&a, (struct sockaddr *)&b) == 0);
}

void test_sockaddr_equal_null() {
    struct sockaddr_in a;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;

    ASSERT("null a", sockaddr_equal(NULL, (struct sockaddr *)&a) == 0);
    ASSERT("null b", sockaddr_equal((struct sockaddr *)&a, NULL) == 0);
    ASSERT("both null", sockaddr_equal(NULL, NULL) == 0);
}

int main() {
    RUN(test_sockaddr_equal_ipv4_same);
    RUN(test_sockaddr_equal_ipv4_different_ip);
    RUN(test_sockaddr_equal_ipv4_different_port);
    RUN(test_sockaddr_equal_ipv6_same);
    RUN(test_sockaddr_equal_ipv6_different_ip);
    RUN(test_sockaddr_equal_different_family);
    RUN(test_sockaddr_equal_null);
    return TEST_REPORT();
}
