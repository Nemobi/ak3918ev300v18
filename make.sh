#!/bin/sh
CUR_PATH=`pwd`
if [ -z "$1" -o "$1" = "kernel" ] ; then
	cd kernel
	if [ ! -d ${CUR_PATH}/build ] ; then
		mkdir ${CUR_PATH}/build
		make O=${CUR_PATH}/build   cloud39ev3_ak3918ev300_corebd_v1.0.0_defconfig
		make O=${CUR_PATH}/build menuconfig
	fi	
	make O=${CUR_PATH}/build -j16 uImage
	if [ $? -ne 0  ] ; then
		exit
	fi
	if [ -f ${CUR_PATH}/build/arch/arm/boot/uImage ] ; then
		cp -f ${CUR_PATH}/build/arch/arm/boot/uImage ${CUR_PATH}/tools/burntool/
	fi
fi


if [ "$1" = "app" ] ; then
	cd ${CUR_PATH}/platform
	make
	if [ $? -ne 0  ] ; then
		exit
	fi
	make install
	make image
fi

if [ "$1" = "kclean" ] ; then
	rm -rf ${CUR_PATH}/build
fi

if [ "$1" = "pclean" ] ; then
	cd ${CUR_PATH}/platform
	make clean
fi

if [ "$1" = "aclean" ] ; then
	rm -rf ${CUR_PATH}/build
	cd ${CUR_PATH}/platform
	make clean
fi

if [ "$1" = "all" ] ; then
	cd kernel
	if [ ! -d ${CUR_PATH}/build ] ; then
		mkdir ${CUR_PATH}/build
		make O=${CUR_PATH}/build   cloud39ev3_ak3918ev300_corebd_v1.0.0_defconfig
		make O=${CUR_PATH}/build menuconfig
	fi	
	make O=${CUR_PATH}/build -j16 uImage
	if [ $? -ne 0  ] ; then
		exit
	fi
	if [ -f ${CUR_PATH}/build/arch/arm/boot/uImage ] ; then
		cp -f ${CUR_PATH}/build/arch/arm/boot/uImage ${CUR_PATH}/tools/burntool/
	fi
	
	cd ${CUR_PATH}/platform
	make
	if [ $? -ne 0  ] ; then
		exit
	fi
	make install
	make image
fi