


haproxy_trace: haproxy_trace.c
	gcc -o $@ $^



test: test_sock_addr


test_sock_addr: test_sock_addr.c sock_addr.h sock_addr.c
	gcc -o $@ $^
