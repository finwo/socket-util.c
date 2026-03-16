#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "socket-util.h"
#include "test.h"

void test_string_to_sockaddr_ipv4() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr("192.168.1.1:8080", &addr);

    ASSERT("ipv4 parse success", result == 0);
    ASSERT("ipv4 family", addr.ss_family == AF_INET);

    struct sockaddr_in *sin = (struct sockaddr_in *)&addr;
    char buf[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET, &sin->sin_addr, buf, sizeof(buf));
    ASSERT_STRING_EQUALS("192.168.1.1", buf);
    ASSERT("ipv4 port", ntohs(sin->sin_port) == 8080);
}

void test_string_to_sockaddr_ipv6() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr("[::1]:3000", &addr);

    ASSERT("ipv6 parse success", result == 0);
    ASSERT("ipv6 family", addr.ss_family == AF_INET6);

    struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&addr;
    char buf[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &sin6->sin6_addr, buf, sizeof(buf));
    ASSERT_STRING_EQUALS("::1", buf);
    ASSERT("ipv6 port", ntohs(sin6->sin6_port) == 3000);
}

void test_string_to_sockaddr_ipv6_full() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr("[2001:db8::1]:443", &addr);

    ASSERT("ipv6 full parse success", result == 0);
    ASSERT("ipv6 full family", addr.ss_family == AF_INET6);

    struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&addr;
    char buf[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &sin6->sin6_addr, buf, sizeof(buf));
    ASSERT_STRING_EQUALS("2001:db8::1", buf);
    ASSERT("ipv6 full port", ntohs(sin6->sin6_port) == 443);
}

void test_string_to_sockaddr_invalid_no_port() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr("192.168.1.1", &addr);
    ASSERT("no port fails", result == -1);
}

void test_string_to_sockaddr_invalid_port() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr("192.168.1.1:99999", &addr);
    ASSERT("invalid port fails", result == -1);
}

void test_string_to_sockaddr_null() {
    struct sockaddr_storage addr;
    int result = string_to_sockaddr(NULL, &addr);
    ASSERT("null string fails", result == -1);
}

int main() {
    RUN(test_string_to_sockaddr_ipv4);
    RUN(test_string_to_sockaddr_ipv6);
    RUN(test_string_to_sockaddr_ipv6_full);
    RUN(test_string_to_sockaddr_invalid_no_port);
    RUN(test_string_to_sockaddr_invalid_port);
    RUN(test_string_to_sockaddr_null);
    return TEST_REPORT();
}
