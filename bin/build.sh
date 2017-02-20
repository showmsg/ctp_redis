#!/bin/sh

BUILD_DIR=$HOME/ctp_redis/target/
CUR_DIR=$HOME/ctp_redis/bin/
MK_ERROR_FILE="output"

SCREEN=`stty -F /dev/console size` 2>/dev/null 
#获取屏幕尺寸大小  默认显示的是横排为25 竖排为80
COLUMNS=${SCREEN#* }                           
#截取屏幕宽度
[ -z $COLUMNS ] && COLUMNS=80                  
#当/dev/console文件不存在，即COLUMNS没有获取到值的时候，直接设置COLUMNS为80
SPA_COL=$[$COLUMNS-12]                         
#总长度-尾部显示字符的大小
#由于显示为[  OK  ]或[ FAILED ]或[ WARNING ]最大值为12
#如果下面自己有调整，这里这个代表长度的12也要调整
  
 
SETCOLOR_SUCCESS='\033[32m'    #设置成功为绿色字
SETCOLOR_FAILURE='\033[31m'    #设置失败为红色字
SETCOLOR_WARNING='\033[33m'    #设置警告为黄色字
SETCOLOR_NORMAL='\033[39m'     #设置普通颜色
BLUE_COLOR='\033[34m'          #蓝
PINK_COLOR='\033[35m'          #粉红
  
#成功后显示OK
success() {
	msg=$1
    RT_SPA=$[$SPA_COL-${#msg}]
    echo -en "${PINK_COLOR} ${msg} ${SETCOLOR_NORMAL}"
    for((i=1;i<=$RT_SPA;i++));do
        echo -n " "
    done
    echo -e "[${SETCOLOR_SUCCESS}    OK    ${SETCOLOR_NORMAL}]" 
    #显示为绿色的OK字体，OK左右有空格，个数可以自己调整
  
}
 
#失败后显示failed
failure() {
    msg=$1
    RT_SPA=$[$SPA_COL-${#msg}]
    echo -en "${PINK_COLOR} ${msg} ${SETCOLOR_NORMAL}"
    for I in `seq 1 $RT_SPA`;do
        echo -n "#"
    done
    echo -e "[${SETCOLOR_FAILURE}  FAILED  ${SETCOLOR_NORMAL}]" 
    #显示为红色的FAILED，FAILED左右有空格，个数可以自己调整
  
}
 
#警告后显示warning
warning() {
	msg=$1
    RT_SPA=$[$SPA_COL-${#msg}]
    echo -en "${PINK_COLOR} ${msg} ${SETCOLOR_NORMAL}"
    for I in `seq 1 $RT_SPA`;do
        echo -n "-"
    done
    echo -e "[${SETCOLOR_WARNING}  WARNING ${SETCOLOR_NORMAL}]" 
    #显示为黄色的WARNING，WARNING左右有空格，个数自己调整
}

cd ${BUILD_DIR}
#清空
echo ${CUR_DIR}${MK_ERROR_FILE}
if [ -f ${CUR_DIR}${MK_ERROR_FILE} ];then
	unlink ${CUR_DIR}${MK_ERROR_FILE}
fi
target=$1
for project in market trade plot
do	
	if [ ${target}"x" == "x" ] || [ ${target}"x" == ${project}"x" ];then
		cd $project
		echo "clear ${project}"
		if [ -f $project ];then
				unlink $project
		fi
		amake $project.prj
		make
		
		if [ -f ${MK_ERROR_FILE} ];then
			cat ${MK_ERROR_FILE}>>${CUR_DIR}${MK_ERROR_FILE}
		fi
		
		cp $project ../../bin/.
		
		if [ -f $project ];then
			success $project
		else
			failure $project
		fi
		cd ..
	fi
done

cd ${CUR_DIR}


