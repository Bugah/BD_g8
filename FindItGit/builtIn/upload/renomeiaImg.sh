#!/bin/bash

ls *.jpg > lista.txt

$i = 0;

for line in $(cat lista.txt);
do

	i=`expr $i + 1` ;

	if [ "$i" -lt 10 ]
	then
		echo "Vetor de IMG00000$i";
		cp $line fmt/IMG00000$i.jpg ;

	else if [ "$i" -lt 100 ]
	then
		echo "Vetor de IMG0000$i";
		cp $line fmt/IMG0000$i.jpg ;


	else    
		if [ "$i" -lt 1000 ]
		then
			echo "Vetor de IMG000$i";
			cp $line fmt/IMG000$i.jpg ;

		else
			if [ "$i" -lt 10000 ]
			then
				echo "Vetor de IMG00$i";
				cp $line fmt/IMG00$i.jpg ;
			fi  
		fi  
	fi  
fi 
done
