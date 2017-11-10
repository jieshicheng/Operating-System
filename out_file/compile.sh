#if [[ ! -d "../lib" || ! -d "../build" ]];then
#	echo "dependent dir don\'t exist!"
#	cwd=$(pwd)
#	cwd=${cwd##*/}
#	cwd=${cwd%/}
#	if [[ $cwd != "out_file" ]];then
#		echo -e "you\'d better in command dir\n"
#	fi
#	exit
#fi

BIN="testFile"
CFLAGS="-Wall -c -fno-builtin -W -Wstrict-prototypes \
		-Wmissing-prototypes -Wsystem-headers"
LIB="../lib/"
OBJS="../build/print.o"
DD_IN=$BIN
DD_OUT="/home/jieshi/bochs-2.6/c.img"

gcc $CFLAGS -I $LIB -o $BIN".o" $BIN".c"
ld -e main $BIN".o" $OBJS -o $BIN
SEC_CNT=$(ls -l $BIN|awk '{printf("%d", ($5+511)/512)}')


	dd if=./$DD_IN of=${DD_OUT} bs=512 count=$SEC_CNT seek=300 conv=notrunc
