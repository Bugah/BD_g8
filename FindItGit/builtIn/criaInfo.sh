echo "$1" > $2.info;
echo "$1" > $2.tags;

./tmp/tools/TableMaker/InsertMySQL 2 5009 $3 $2.tags
