#!/bin/bash

if [ -n "$1" ]
then 
    PROGRAM=$1
else
    echo "Specify filename of program to test"
    exit $E_WRONGARGS
fi


echo "START TESTING $PROGRAM"
for file in $(ls in/)
do
    echo -n "Test $file: "
    $(./$PROGRAM -c out/$file.hf in/$file)
	$(./$PROGRAM -x out/$file out/$file.hf)
    $(diff in/$file out/$file > diff/$file.diff)

	if [ $(cat diff/$file.diff | wc -c) -eq 0 ] 
	then
		echo "SUCCEED"
	else 
		echo "!SUCCEED:"
		$(cat diff/$file.diff)
    fi
    echo "==="
done

exit 0
