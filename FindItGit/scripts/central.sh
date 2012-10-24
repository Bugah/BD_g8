#!/bin/bash
mainDir="/var/www/html/FindItGit"


echo -e "\n\n-- Opções"
echo "1) Copiar/Atualizar diretório para o local correto"
echo "2) Corrigir permissões do local correto"
echo "3) Abrir direto o site"
echo "4) Copiar banco de imagens para o diretório correto"
echo "5) Criar Thumbnails"
echo "6) Importar Banco de Dados-Base"
echo "7) Sair"


while true
	read -r op
do
	case "$op" in
		"1")
			echo Criando novo diretório, se não existir
			!(mkdir /var/www/html/) && echo -e "Já existe o diretório...\nCopiando arquivos..."
			cp -Rf .. $mainDir
			echo -e "Diretório de FindIt encontrado em /var/www/html/FindItGit\n\n"
			;;

		"2")
			cd $mainDir
			echo "Corrindo permissões..."
			sh permissoes.sh
			echo Pronto!
			;;

		"3")
			echo "Abrindo o arquivo principal"
			firefox localhost/FindItGit &
			;;
		"4")	
			echo "Digite o diretório origem das imagens .jpg"
			read -r dir
			!(test -d $dir) && echo "'$dir' não é um diretório válido..."
			cp $dir/*.jpg $mainDir/builtIn/upload/fmt/
			echo "Pronto!"
			;;

		"5")	echo "Criando thumbnails (pode levar 10 minutos...) Assegure-se de que há imagens .jpg no diretório correto (Passo 2)"
			cd $mainDir/builtIn/upload/fmt/
			sh compactaImgJPEG2000.sh
			echo "Pronto!"
			;;
		"6")	echo "Importando banco de dados"
			mysql -u root test < $mainDir/mysql.sql;
			echo "Pronto!"
			;;
		"7")
			exit
			;;

		*)
			echo -e "\n\n-- Opções"
			echo "1) Copiar/Atualizar diretório para o local correto"
			echo "2) Corrigir permissões do local correto"
			echo "3) Abrir direto o site"
			echo "4) Copiar banco de imagens para o diretório correto"
			echo "5) Criar Thumbnails"
			echo "6) Importar Banco de Dados-Base"
			echo "7) Sair"
			;;
	esac
done

