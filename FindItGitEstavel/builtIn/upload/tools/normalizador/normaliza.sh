#!/bin/bash
echo "Arquivo $2$1.jpg "
pwd

!(test -f "$2$1.jpg") && echo "Arquivo $2$1.jpg não é válido" && exit

echo python caracterizar.py $2$1.jpg $2$1
python caracterizar.py $2$1.jpg $2$1

echo python projeta.py $2$1.key dicionario-1000.pal $2$1
python projeta.py $2$1.key dicionario-1000.pal $2$1

echo python normalizar.py $2$1.hist $2$1
python normalizar.py $2$1.hist $2$1
