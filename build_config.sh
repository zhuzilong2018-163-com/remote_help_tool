#!/bin/bash
FILE="config.mk"

if [ ! -f "$FILE" ]; then
 touch "$FILE"
 chmod 777 "$FILE"
else
 rm "$FILE"
 touch "$FILE"
 chmod 777 "$FILE"
fi

if [ "$1" = "debug" ]; then
 MODE="-DMODE"
 echo "debug mode"
else
 MODE=""
 echo "release"
fi

COMMON=$(pwd)/common
SERVER=$(pwd)/server
CLIENT=$(pwd)/client
OUTPUT=$(pwd)/target
COMM_INCLUDE=$(pwd)/common/inc
RELEASE=$(pwd)/target/release
RELEASE_LIB=$(pwd)/target/lib
RELEASE_BIN=$(pwd)/target/bin
echo COMMON=$COMMON >> $FILE
echo SERVER=$SERVER >> $FILE
echo CLIENT=$CLIENT >> $FILE
echo OUTPUT=$OUTPUT >> $FILE
echo COMM_INCLUDE=$COMM_INCLUDE >> $FILE
echo CC=gcc >> $FILE
echo STRIP=strip >> $FILE
echo AR=ar >> $FILE
echo CXX=g++ >> $FILE
echo RELEASE=$RELEASE >> $FILE
echo RELEASE_LIB=$RELEASE_LIB >> $FILE
echo RELEASE_BIN=$RELEASE_BIN >> $FILE
echo "build config.mk successful!"

