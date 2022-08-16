
CFLAGS=-g -g3



all: haproxy_trace get_sess

dst: all
	tar czf haproxy_trace.tar.gz haproxy_trace get_sess haproxy_trace.sh

haproxy_trace: haproxy_trace.c fd_sock.c sock_addr.c fd_route.c
	gcc -static -o $@ $^


get_sess: get_sess.c
	gcc -static -o $@ $^

test: test_sock_addr test_fd_sock test_fd_route


test_fd_sock: test_fd_sock.c fd_sock.h fd_sock.c
	gcc $(CFLAGS) -DDEBUG -o $@ $^

test_sock_addr: test_sock_addr.c sock_addr.h sock_addr.c
	gcc $(CFLAGS) -DDEBUG -o $@ $^

test_fd_route: test_fd_route.c fd_route.c sock_addr.c fd_sock.c
	gcc $(CFLAGS) -DDEBUG -I . -o $@ $^


tags:
	ctags -R .

clean:
	rm -f test_sock_addr test_fd_sock test_fd_route haproxy_trace get_sess

.PHONY: tags clean dst
