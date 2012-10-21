#!/bin/bash

TOTAL="5000"			# numero de arquivos
i="1"				# iterador
NOREXTENSION=".nor"		# extensao .nor
TAGSEXTENSION=".tags"           # extensao .tags
NORPATH="norFiles/"		# path dos arquivos .nor
TAGSPATH="jpgFiles/"            # path dos arquivos .jpg
CONTROL="0"

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
	
	if [ $CONTROL = "200" ]; then
		echo $i Gone!
		CONTROL="0"
	fi
	
	CONTROL=$[$CONTROL+1]
	
	
	if [ -e $NORPATH$FILENAME$i$NOREXTENSION ]			# testa existencia
	then
		if [ -s $NORPATH$FILENAME$i$NOREXTENSION ]		# testa se esta vazio
		then
			#echo ./InsertMySQL 1 $i $NORPATH$FILENAME$i$NOREXTENSION a.nor b.nor c.nor d.nor
			./InsertMySQL 1 $i $NORPATH$FILENAME$i$NOREXTENSION 1.nor 2.nor 3.nor 4.nor 5.nor 6.nor 7.nor 8.nor 9.nor 10.nor
                        # Arquivo encontrado e com algum texto, insere no banco VECTORS
			
			#echo ./InsertMySQL 2 $i $FILENAME$i $TAGSPATH$FILENAME$i$TAGSEXTENSION
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