#!/bin/bash

TOTAL="5000"			# numero de arquivos
i="1"					# iterador
NOREXTENSION=".nor"		# extensao .nor
TAGSEXTENSION=".tags"	# extensao .tags
NORPATH="norFiles/"		# path dos arquivos .nor
TAGSPATH="jpgFiles/"	# path dos arquivos .jpg

TOTAL=$[$TOTAL+1]		# inicializa

./CreateTablesMySQL 1	# DropTable e Create Table Vector
./CreateTablesMySQL 2	# DropTable e Create Table TABIMG


while [ $i -lt $TOTAL ]; do
	#echo Adicionando $i th foto.
	if [ $i -lt 10 ]; then
		FILENAME="IMG00000"
	else
		if [ $i -lt 100 ]; then
			FILENAME="IMG0000"
		else
			if [ $i -lt 1000 ]; then
			FILENAME="IMG000"		
			else
				FILENAME="IMG00"
			fi
		fi
	fi
	
	if [ -e $NORPATH$FILENAME$i$NOREXTENSION ]			# testa existencia
	then
		if [ -s $NORPATH$FILENAME$i$NOREXTENSION ]		# testa se esta vazio
		then
			echo ./InsertMySQL 1 $i $NORPATH$FILENAME$i$NOREXTENSION
			./InsertMySQL 1 $i $NORPATH$FILENAME$i$NOREXTENSION
		    # Arquivo encontrado e com algum texto, insere no banco VECTORS
			
			echo ./InsertMySQL 2 $i $FILENAME$i $TAGSPATH$FILENAME$i$TAGSEXTENSION 
			./InsertMySQL 2 $i $FILENAME$i $TAGSPATH$FILENAME$i$TAGSEXTENSION 
			# insere no banco TABIMG
		else
			echo Arquivo $i vazio.
		fi
	else
		echo Arquivo $i nao encontrado.
	fi 
	
	i=$[$i+1]
done