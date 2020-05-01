#!/bin/sh
FILE="monitor"
if [ ! -f "$FILE" ]; then
 ./$FILE
else
 echo "The process of monitor can't creat"
fi