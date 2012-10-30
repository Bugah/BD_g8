#!/bin/bash

date=$(date -dtoday +%Y%m%d);

echo "Digite o diretório de backup"
read -r b
!(test -d "$b") && echo "Diretório $b não é válido" && exit
tar cvf findit$date.tar $b && bzip2 findit$date.tar
