#!/bin/bash

if [ -n "$1" ]
then 
    PROGRAM=$1
else
    echo "Specify filename of program to test"
    exit $E_WRONGARGS
fi

FILE="test"
md5sum final_test/$FILE.in
$(time $(./$PROGRAM -c final_test/$FILE.hf final_test/$FILE.in &&
        ./$PROGRAM -x final_test/$FILE.out final_test/$FILE.hf) )
md5sum final_test/$FILE.out
exit 0
