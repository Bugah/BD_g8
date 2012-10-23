#!/bin/bash

(test -d "$2") && cd $2 && echo "Mudou diretório"

!(test -f "$1.jpg") && echo "Arquivo $1.jpg não é válido" && exit

echo python caracterizar.py $1.jpg $1
python caracterizar.py $1.jpg $1

echo python projeta.py $1.key dicionario-1000.pal $1
python projeta.py $1.key dicionario-1000.pal $1

echo python normalizar.py $1.hist $1
python normalizar.py $1.hist $1
