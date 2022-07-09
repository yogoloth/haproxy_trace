#!/bin/bash

#pid=3321

pid=`ps ax| grep haproxy| grep -v grep| awk 'NR==1{print $1}'`

proc_file=/proc/net/tcp
tmp_proc_file=/tmp/proc_file
tmp_socket_file=/tmp/socket_file
tmp_sess=/tmp/haproxy_sess

cp $proc_file $tmp_proc_file
ls -lh /proc/$pid/fd/ |grep socket: | awk '{print $9" "$11}' >$tmp_socket_file
#cat /dev/null >$tmp_socket_file
#for pid in `ps ax| grep haproxy | grep -v wrapper | grep -v grep| awk '{print $1}'`;do
    #ls -lh /proc/$pid/fd/ |grep socket: | awk '{print $9" "$11}' >>$tmp_socket_file
#    ls -lh /proc/$pid/fd/ |grep socket: | awk '{print $9" "$11}' >$tmp_socket_file
#done

#echo show sess| socat /var/lib/haproxy/stats stdio | grep -v fd=-1 | awk '{print $3" "$4" "$5" "$12" "$13 }'| sed 's/s0=\[.*fd=\([0-9]\+\).*\].*s1=.*\[.*fd=\([0-9]\+\).*\]/\1 \2/g' >$tmp_sess
echo show sess| socat /var/lib/haproxy/stats stdio | grep -v fd=-1 | awk '{print $3" "$4" "$5" "$16" "$17 }'| sed 's/s0=\[.*fd=\([0-9]\+\).*\].*s1=.*\[.*fd=\([0-9]\+\).*\]/\1 \2/g' >$tmp_sess



cat $tmp_sess| \
while read src fe be fd1 fd2
do 
[ -z "$src" ]&&exit
addr1=`~/fd2ports.sh $pid $fd1 $tmp_proc_file $tmp_socket_file from`
addr2=`~/fd2ports.sh $pid $fd2 $tmp_proc_file $tmp_socket_file to`
echo  $src $fe $be $addr1 "-->" $addr2
#sleep 1

done;
