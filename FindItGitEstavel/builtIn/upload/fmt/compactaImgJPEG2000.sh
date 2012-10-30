#!/bin/bash

# Faz a lista de arquivos jpg a serem comprimidos
ls *.jpg > lista.txt
i=0

for line in $(cat lista.txt);
do
	if [ `expr $i % 100` -eq 0 ]
	then
		echo -ne "|" 
	fi
	i=`expr $i + 1`;
	convert $line -compress JPEG2000 -quality 75 -thumbnail 550\> cmp/$line ;
done
