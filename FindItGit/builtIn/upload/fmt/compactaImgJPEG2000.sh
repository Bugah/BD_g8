#!/bin/bash

# Faz a lista de arquivos jpg a serem comprimidos
ls *.jpg > lista.txt

for line in $(cat lista.txt);
do

	convert $line -compress JPEG2000 -quality 75 -thumbnail 550\> cmp/$line ;
done
