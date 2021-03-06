#! /bin/sh
### BEGIN INIT INFO
# File:				eth_manage.sh	
# Required-Start:   $
# Required-Stop:
# Default-Start:     
# Default-Stop:
# Description: ethernet manager
# Author:			
# Email: 			
# Date:				2014-8-8
### END INIT INFO

MODE=$1
PATH=$PATH:/bin:/sbin:/usr/bin:/usr/sbin
INI_FILE="/etc/jffs2/onvif_cfg.ini"

usage()
{
	echo "Usage: $0 start|stop|restart)"
	exit 3
}

stop()
{
	echo "stop ethernet......"
	killall udhcpc
}

use_static_ip()
{
	ipaddr=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/ipaddr/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	netmask=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/netmask/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	gateway=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/gateway/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	firstdns=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/firstdns/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	backdns=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/backdns/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	ifconfig eth0 $ipaddr netmask $netmask
	route add default gw $gateway
	sed -i "2,\$c nameserver $firstdns \
		nameserver $backdns" /etc/jffs2/resolv.conf

	echo 0 > /tmp/dhcp_status  ### record non-dhcp status
	sleep 1
}

check_ip_and_start()
{
	i=0

	dhcp=`awk 'BEGIN {FS="="}/\[ethernet\]/{a=1} a==1&&$1~/dhcp/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);gsub(/^[[:blank:]]*/,"",$2);print $2}' ${INI_FILE}`

	if [ $dhcp -eq 0 ]
	then
		echo "using static ip address..."
		use_static_ip
		status=ok
	else
		status=

		while [ $i -lt 2 ]
		do
			cable=`ifconfig eth0 | grep RUNNING`
			if [ "$cable" = "" ]
			then
				echo "Network cable has been unplug!"
				return
			fi

			echo "Getting ip address..."
			killall udhcpc
			udhcpc -i eth0 &

			####  sleep 5 seconds, because some router allocate IP address is too slow
			sleep 5

			status=`ifconfig eth0 | grep "inet addr:"`
			if [ -z "$status" ];then
				i=`expr $i + 1`
			else
				echo 1 > /tmp/dhcp_status ### record dhcp status
				break
			fi
		
		done

		status=`ifconfig eth0 | grep "inet addr:"`
		if [ "$status" = "" ] && [ $i -eq 2 ];then
			echo "can't getting ip address by dynamic, using static ip address!"
			killall udhcpc
			use_static_ip
		fi
	fi
	
	/usr/sbin/led.sh off
}

start ()
{
	echo "start ethernet......"
	check_ip_and_start
}

restart ()
{
	echo "restart ethernet......"
	stop
	start
}

#
# main:
#
case "$MODE" in
	start)
		start
		;;
	stop)
		stop
		;;
	restart)
		restart
		;;
	*)
		usage
		;;
esac

exit 0