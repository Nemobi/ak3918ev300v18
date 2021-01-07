#! /bin/sh
### BEGIN INIT INFO
# File:				net_manage.sh
# Provides:         start ethernet
# Required-Start:   $
# Required-Stop:
# Default-Start:
# Default-Stop:
# Short-Description
# Author:
# Email:
# Date:				2013-1-15
### END INIT INFO


#
#main
#

#Do load ethernet module?
if [ ! -d "/sys/class/net/eth0" ]                                                                   #�ж��Ƿ����eth�豸
then
	echo "[net manage] the ethernet module is not initialize"
	exit 1                                                                                      #���������˳�
else
	ifconfig eth0 up
	cable_last=0                                                                                #��ʼ��Ĭ�Ͻ���һ������״̬����Ϊδ����
	while true                                                                                  #����ѭ���ж�
	do
		sleep 2
		status=`ifconfig eth0 | grep RUNNING`                                               #ͨ���ж�RUNNING�Ƿ����,���õ�ǰ�����߲���״̬
		if [ -n "$status" ]
		then
			cable_now=1                                                                 #���߽�������Ϊ1
		else
			cable_now=0                                                                 #����δ��������Ϊ0
		fi
		#echo "cable_last=$cable_last cable_now=$cable_now"
		if [ $cable_last -lt $cable_now ]                                                   #֮ǰ����״̬Ϊδ����,����ǰ����״̬Ϊ����,������eth�ű������������
		then
			/usr/sbin/eth_manage.sh start                                               #������̫�����ӽű�
		fi
		cable_last=$cable_now                                                               #���汾�ε����߽���״̬
	done
fi

exit 0