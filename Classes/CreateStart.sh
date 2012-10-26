#!/bin/bash

OUTPUT="1.nor"
TOTAL="800"
TOTAL2="100"
TOTAL3="100"			
i="1"				# iterador
j="1"
VALUE="0.001"
VALUE2="0.001"
VALUE3="0.001"
JOIN=" $VALUE"
COUNT="1"
	
while [ $i -lt $TOTAL ]; do
	JOIN="$JOIN $VALUE"
	i=$[$i+1]
	COUNT=$[$COUNT+1]
done

JOIN="$JOIN $VALUE2"
j="1"
COUNT=$[$COUNT+1]

while [ $j -lt $TOTAL2 ]; do
	JOIN="$JOIN $VALUE2"
	j=$[$j+1]
	COUNT=$[$COUNT+1]
done

JOIN="$JOIN $VALUE3"
COUNT=$[$COUNT+1]
k="1"

while [ $k -lt $TOTAL3 ]; do
	JOIN="$JOIN $VALUE3"
	k=$[$k+1]
	COUNT=$[$COUNT+1]
done

JOIN="$JOIN 1"

echo COUNT : $COUNT

echo $JOIN >> $OUTPUT

#while [ $i -lt $FULLTOTAL ]; do
#	i=$[$i+1]
#done

#echo 0 >> a.nor