#!/bin/bash
echo "Iniciando... Se quiser cancelar agora, digite 'q' seguido de <enter>, senão digite qualquer outra coisa";
    
read -r conf
if [ "$conf" == "q" ]
then
	exit
fi

mainDir="/var/www/html/FindItGit"

echo Criando novo diretório, se não existir
!(mkdir /var/www/html/) && echo -e "Já existe o diretório...\nCopiando arquivos..."
cp -Rf .. $mainDir
echo -e "Diretório de FindIt encontrado em /var/www/html/FindItGit\n\n"

cd $mainDir
echo "Corrindo permissões..."
sh permissoes.sh
echo Pronto!

echo -e "\n\n-- Opções"
echo "1) Abrir direto o site"
echo "2) Copiar banco de imagens para o diretório correto"
echo "3) Criar Thumbnails"
echo "4) Importar banco de dados do Mocó"
echo "5) Sair"


while true
read -r op
do
	case "$op" in
	
	"1")
		echo "Abrindo o arquivo principal"
		firefox localhost/FindItGit &
		;;
	"2")	
		echo "Digite o diretório origem das imagens"
			read -r dir
			!(test -d $dir) && echo "'$dir' não é um diretório válido..."
			cp $dir/*.jpg $mainDir/builtIn/upload/fmt/
			echo "Pronto!"
			;;

	"3")	echo "Criando thumbnails (pode levar 10 minutos...) Assegure-se de que há imagens .jpg no diretório correto (Passo 2)"
			cd $mainDir/builtIn/upload/fmt/
			sh compactaImgJPEG2000.sh
			echo "Pronto!"
			;;
	"4")	echo "Importando banco de dados"
			mysql -u root test < $mainDir/mysql.sql;
			echo "Pronto!"
			;;
	"5")
		exit
		;;

	*)
		echo "-- Opções"
		echo "1) Abrir direto o site"
		echo "2) Copiar banco de imagens para o diretório correto"
		echo "3) Criar Thumbnails"
		echo "4) Importar banco de dados do Mocó"
		echo "5) Sair"
		;;
	esac
done

