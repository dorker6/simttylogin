#!/usr/bin/env sh
PRINTCMD=$(command -v printf || command -v echo -ne)
FILE="./simttylogin"
CFGFILE=$FILE.conf

if [ $(id -u) -ne 0 ]; then
	$PRINTCMD "please run as root\n"
	exit 1
fi

if [ ! -e $FILE  ]; then
	$PRINTCMD $FILE
	$PRINTCMD " doesn't exist\n" 
	$PRINTCMD "did you run ./compile.sh\n"
	exit 1
fi
install -s -m 0755 $FILE /usr/bin/ || $PRINTCMD "installing binary failed\n" exit 1
install -m 0644 $CFGFILE /etc/pam.d/simttylogin || $PRINTCMD "instaling pam configuration file failed\n" exit 1
$PRINTCMD "installed sucesfully\n"
