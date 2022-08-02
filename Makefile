
CFLAGS=-g -g3

haproxy_trace: haproxy_trace.c fd_sock.c sock_addr.c
	gcc -o $@ $^



test: test_sock_addr test_fd_sock


test_fd_sock: test_fd_sock.c fd_sock.h fd_sock.c
	gcc $(CFLAGS) -DDEBUG -o $@ $^

test_sock_addr: test_sock_addr.c sock_addr.h sock_addr.c
	gcc $(CFLAGS) -DDEBUG -o $@ $^


tags:
	ctags -R .

clean:
	rm -f test_sock_addr test_fd_sock haproxy_trace

.PHONY: tags clean
