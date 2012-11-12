#!/bin/bash

# Faz a lista de arquivos jpg a serem comprimidos
ls *.jpg > lista.txt
i=0

# Cria o diretório dos thumbnails
mkdir cmp

for line in $(cat lista.txt);
do
	if [ `expr $i % 100` -eq 0 ]
	then
		echo -ne "|" 
	fi
	i=`expr $i + 1`;
	convert $line -compress JPEG2000 -quality 75 -thumbnail 500\> cmp/$line ;
done
