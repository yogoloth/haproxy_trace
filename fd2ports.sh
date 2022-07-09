#!/bin/bash


pid=$1

fd=$2

proc_file=${3:-/proc/net/tcp}


tmp_socket_file=${4:-/tmp/socket_file}

dirt=$5

#ls -lh /proc/$pid/fd/ | awk '{print $9" "$11}' >$tmp_socket_file


socket=`awk '$1=='$fd'{print $2;exit}' $tmp_socket_file`

[[ -z "$socket" ]]&& echo $fd disappear >/dev/stderr && echo "0:0 --> 0:0" && exit

socket_no=`echo $socket| sed 's/socket:\[\([0-9]\+\)\]/\1/'`

#echo $socket_no




function hex2port(){
    echo $((0x$1))
}

function hex2ip(){
   for i in `echo $1| sed 's/\(..\)\(..\)\(..\)\(..\)/\4 \3 \2 \1/'`;do echo $((0x$i)) ;done | paste -d \. -s
}

function hexaddr2addr(){
    hexip=`echo $1|cut -d : -f 1`
    hexport=`echo $1|cut -d : -f 2`
    echo `hex2ip $hexip`:`hex2port $hexport`
}



hex_addrs=(`awk '$10=='$socket_no'{print $2" "$3;exit}' ${proc_file}`)

src=`hexaddr2addr ${hex_addrs[0]}`
dest=`hexaddr2addr ${hex_addrs[1]}`

if [ $dirt = "to" ];then
  echo $src "-->" $dest
else
  echo $dest "-->" $src
fi


