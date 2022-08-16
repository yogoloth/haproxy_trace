#!/bin/bash

#pid=3321

haproxy_socket=${1:-/var/lib/haproxy/stats}

pid=`ps ax| grep haproxy| grep -v grep| awk 'NR==1{print $1}'`

proc_file=/proc/net/tcp
tmp_proc_file=/tmp/proc_file
tmp_socket_file=/tmp/socket_file
tmp_sess=/tmp/haproxy_sess

cp $proc_file $tmp_proc_file
ls -lh /proc/$pid/fd/ |grep socket: | awk '{print $9" "$11}' >$tmp_socket_file
#echo show sess| socat /var/lib/haproxy/stats stdio | grep -v fd=-1 | awk '{print $3" "$4" "$5" "$16" "$17 }'| sed 's/s0=\[.*fd=\([0-9]\+\).*\].*s1=.*\[.*fd=\([0-9]\+\).*\]/\1 \2/g' >$tmp_sess
./get_sess ${haproxy_socket} stdio | grep -v fd=-1 | awk '{print $3" "$4" "$5" "$16" "$17 }'| sed 's/s0=\[.*fd=\([0-9]\+\).*\].*s1=.*\[.*fd=\([0-9]\+\).*\]/\1 \2/g' >$tmp_sess


./haproxy_trace $tmp_sess $tmp_proc_file $tmp_socket_file

