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

if [ ! -d "/sys/class/net/wlan0" ]
then
	/usr/sbin/wifi_driver.sh station
	ifconfig wlan0 up
fi
#/usr/sbin/wifi_led.sh LED_B blink 200
exit 0

