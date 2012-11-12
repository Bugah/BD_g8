#Criando os arquivos a partir das strings de entrada
echo "$1" > $3.desc;
echo "$2" > $3.tags;

#Inserindo imagem no banco de dados
echo $3
echo ./tmp/tools/TableMaker/InsertMySQL 2 "$5" "$4" "$3".tags
./tmp/tools/TableMaker/InsertMySQL 2 "$5" "$4" "$3".tags
