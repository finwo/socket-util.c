#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "socket-util.h"
#include "test.h"

void test_sockaddr_to_string_ipv4() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &addr.sin_addr);
    addr.sin_port = htons(8080);

    char buf[INET6_ADDRSTRLEN + 8];
    sockaddr_to_string((struct sockaddr *)&addr, buf, sizeof(buf));

    ASSERT_STRING_EQUALS("192.168.1.1:8080", buf);
}

void test_sockaddr_to_string_ipv6() {
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &addr.sin6_addr);
    addr.sin6_port = htons(3000);

    char buf[INET6_ADDRSTRLEN + 8];
    sockaddr_to_string((struct sockaddr *)&addr, buf, sizeof(buf));

    ASSERT_STRING_EQUALS("[::1]:3000", buf);
}

void test_sockaddr_to_string_ipv6_full() {
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "2001:db8::1", &addr.sin6_addr);
    addr.sin6_port = htons(443);

    char buf[INET6_ADDRSTRLEN + 8];
    sockaddr_to_string((struct sockaddr *)&addr, buf, sizeof(buf));

    ASSERT_STRING_EQUALS("[2001:db8::1]:443", buf);
}

void test_sockaddr_to_string_null() {
    char buf[64] = "initial";
    sockaddr_to_string(NULL, buf, sizeof(buf));
    ASSERT("null addr doesn't crash", 1);
}

int main() {
    RUN(test_sockaddr_to_string_ipv4);
    RUN(test_sockaddr_to_string_ipv6);
    RUN(test_sockaddr_to_string_ipv6_full);
    RUN(test_sockaddr_to_string_null);
    return TEST_REPORT();
}
