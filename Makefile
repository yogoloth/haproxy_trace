
CFLAGS=-g -g3

haproxy_trace: haproxy_trace.c
	gcc -o $@ $^



test: test_sock_addr


test_sock_addr: test_sock_addr.c sock_addr.h sock_addr.c
	gcc $(CFLAGS) -DDEBUG -o $@ $^


tags:
	ctags -R .

clean:
	rm test_sock_addr haproxy_trace
