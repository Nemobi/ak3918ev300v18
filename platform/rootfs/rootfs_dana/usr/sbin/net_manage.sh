#! /bin/sh
### BEGIN INIT INFO
# File:				net_manage.sh
# Provides:         select eth or wifi
# Required-Start:   $
# Required-Stop:
# Default-Start:
# Default-Stop:
# Short-Description
# Author:
# Email:
# Date:				2013-1-15
### END INIT INFO

CM_NORMAL=0
CM_BOLD=1
CM_UNDERLINED=4
CM_BLINK=5
CM_NEGATIVE=7

CB_BLACK=40
CB_RED=41
CB_GREEN=42
CB_YELLOW=43
CB_BLUE=44
CB_PURPLE=45
CB_CYAN=46
CB_WHITE=47

CF_BLACK=30
CF_RED=31
CF_GREEN=32
CF_YELLOW=33
CF_BLUE=34
CF_PURPLE=35
CF_CYAN=36
CF_WHITE=37

mode=""
status=""
ping_time=0                                                                                         #ping��ǰ��ʱ����
cfgfile="/etc/jffs2/anyka_cfg.ini"

ping_enable=`awk 'BEGIN {FS="="}/\[ping\]/{a=1} a==1 &&
			$1~/^ping_enable/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);
			gsub(/^[[:blank:]]*/,"",$2);print $2}' $cfgfile`                                        #pingʹ��
ping_try=`awk 'BEGIN {FS="="}/\[ping\]/{a=1} a==1 &&
			$1~/^ping_try/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);
			gsub(/^[[:blank:]]*/,"",$2);print $2}' $cfgfile`                                        #pingʧ�����Դ���
ping_split=`awk 'BEGIN {FS="="}/\[ping\]/{a=1} a==1 &&
			$1~/^ping_split/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);
			gsub(/^[[:blank:]]*/,"",$2);print $2}' $cfgfile`                                        #ping��֤���
ping_ip_static=`awk 'BEGIN {FS="="}/\[ping\]/{a=1} a==1 &&
			$1~/^ping_ip/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);
			gsub(/^[[:blank:]]*/,"",$2);print $2}' $cfgfile`                                        #ping��ʹ�õ�ip��ַ
ping_type=`awk 'BEGIN {FS="="}/\[ping\]/{a=1} a==1 &&
			$1~/^ping_type/{gsub(/\"/,"",$2);gsub(/\;.*/, "", $2);
			gsub(/^[[:blank:]]*/,"",$2);print $2}' $cfgfile`                                        #ping��ʹ�õ���֤��ʽping/arping

if [ -n "$ping_ip_static" ] ; then                                                                  #�Ƿ��Ѿ��������ж�ȡ��ping_ip
	ping_ip=$ping_ip_static
fi
echo -e "\e["$CM_NORMAL";"$CF_BLUE";"$CB_BLACK"m""ping_enable=$ping_enable ping_try=$ping_try ping_split=$ping_split ping_type=$ping_type ping_ip=$ping_ip""\e[0m"

wlan_ping()
{
	let ping_time=$ping_time+1
	if [ $ping_time -ge $ping_split ] ; then                                                        #�ж���ǰʱ�����Ƿ��Ѿ��ﵽ
		gw_ip=`route -n | grep -E "^0.0.0.0.*wlan[0-9]" | awk '{print $2}'`                         #��ȡ����ip��ַ
		if [ -z "$ping_ip_static" ] ; then                                                          #�ж��Ƿ����û�о�̬��֤ip��ַ
			ping_ip=$gw_ip                                                                          #�����ļ�ipΪ����ʹ������ip������֤
		fi
		if [ -n "$gw_ip" ] ; then                                                                   #�ж�gw_ip��ַ�Ƿ�Ϊ��,�Ƿ��ȡҪ��֤��ip��ַ
			#echo -e "\e["$CM_NORMAL";"$CF_BLUE";"$CB_BLACK"m""TRY_PING '$ping_ip'""\e[0m"
			i=0
			while [ $i -lt $ping_try ]                                                              #ѭ��ping_try��ȥ����ping��֤�����Ƿ���ͨ
			do
				if [ $ping_type -eq 0 ]
				then                                                                                #ʹ��ping
					ping -W 1 -c 1 $ping_ip > /dev/null
					ping_res=$?
					#echo -e "\e["$CM_NORMAL";"$CF_BLUE";"$CB_BLACK"m"`date`" PING $ping_res""\e[0m"
				else                                                                                #ʹ��arping
					arping -c 1 -w 1 -I wlan0 $ping_ip > /dev/null
					ping_res=$?
					#echo -e "\e["$CM_NORMAL";"$CF_BLUE";"$CB_BLACK"m"`date`" ARPING $ping_res""\e[0m"
				fi
				if [ $ping_res -ne 0 ]                                                              #���ؽ����Ϊ0��Ϊping��ͨ
				then                                                                                #��֤ʧ��
					echo -e "\e["$CM_NORMAL";"$CF_RED";"$CB_BLACK"m"`date`" PING $ping_ip FAIL""\e[0m"
				else                                                                                #��֤�ɹ�
					#echo -e "\e["$CM_NORMAL";"$CF_GREEN";"$CB_BLACK"m"`date`" PING $ping_ip SUCCESS""\e[0m"
					let ping_time=0
					return 0
				fi
				let i=$i+1
			done
			mode=""                                                                                 #ping��֤ʧ��,��mode����Ϊ�գ���check_and_start_wlan��������
			return 1
		fi
		let ping_time=0
	fi
	return 0
}

check_and_start_wlan()
{
	#echo -e "\e["$CM_NORMAL";"$CF_BLUE";"$CB_BLACK"m""$mode $ping_time $ping_enable $ping_split""\e[0m"
	if [ "$mode" != "wlan" ]; then
		mode=wlan
		ip=`ifconfig eth0 | grep 'inet addr' | awk '{print $2}' | awk -F ':' '{print $2}'`
		ipaddr del $ip dev eth0
		ifconfig eth0 down
		/usr/sbin/wifi_manage.sh start
		ifconfig eth0 up
	elif [ $ping_enable -eq 1 ]; then                                                               #ping_enableʹ�ܿ����Ƿ�Ϊ1,�ж��Ƿ����ping��֤
		wlan_ping
		if [ $? -ne 0 ]
		then
			/usr/sbin/wifi_manage.sh stop
		fi
	fi
}

check_and_start_eth()
{
	if [ "$mode" != "eth" ]
	then
		mode=eth
		/usr/sbin/wifi_manage.sh stop
		/usr/sbin/eth_manage.sh start
	fi
}


#
#main
#

#Do load ethernet module?

if [ ! -d "/sys/class/net/eth0" ]
then
	/usr/sbin/wifi_manage.sh start
	exit 1
else
	#ethernet always up
	ifconfig eth0 up
	sleep 3
fi

status=`ifconfig eth0 | grep RUNNING`
while true
do
	#check whether insert internet cable

	if [ "$status" = "" ]
	then
		#don't insert internet cable
		check_and_start_wlan
	else
		#have inserted internet cable
		check_and_start_eth
	fi

	tmp=`ifconfig eth0 | grep RUNNING`
	if [ "$tmp" != "$status" ]
	then
		sleep 2
		tmp=`ifconfig eth0 | grep RUNNING`
		status=$tmp
	fi
	sleep 1
done
exit 0

