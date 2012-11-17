/*
 * main.cpp
 * Created 		on: Oct 29, 2012
 * Last Changed on: Oct 30, 2012
 * Author: andre
 */

#include <fstream>
#include <stdlib.h>
#include <iomanip> // Formatação da saída para interface
#include "Text.h"
#include "mysql_header.h"
using namespace sql;

/* Monta a Query e faz o aninhamento das tags, respectivamente */
string inner_join(Text, Text);

/**
 * Programa que irá executar todas as querys, utilizando a classe
 * Text como auxiliar para montá-las e adequar o seu resultado
 * OBS: Esta versao ainda nao trata tags relacionadas
 * */

int main(int argc, char * argv[]) {
	/* Declaracoes */
	size_t i, count = 0;
	int j;
	string str, tmp; // Retiram os valores no arquivo
	Text tags, aux, dicio, asw; // Tags retiradas do texto

	// Arquivos de Entrada e Saida
	ifstream infile; // Arquivo com dicionario de Tags

	/* Objetos MySQL */
	sql::mysql::MySQL_Driver * driver;
	sql::Connection * con;
	sql::Statement * stmt;
	sql::ResultSet * res;
	/* Fim das Declaracoes */

	/* Faz a conversao do texto digitado para objetos texto */
	for (j = 1; j < (size_t) argc; j++)
		tags += argv[j];

	// Abre o Dicionario de tags
	infile.open("dicionarioTags.tags");
	if (infile.is_open()) {
		getline(infile, str);
		dicio = str;
	} else {
		cout << "Arquivo de Dicionario nao Encontrado! Processo Abortado!"
				<< endl;
		return -1;
	}
	aux = tags - dicio;
	tags -= aux;
	tags.no_repeat();
	/* Fim da conversao do texto */

	/* Faz a inicializacao do Vector de Aninhamento
	 * Comeca com todos os valores em AND
	 * */

	if (tags.getSize() == 0) {
		cout << "Nenhuma tag encontrada na descricao!" << endl;
		return -1;
	}

	/* Agora criamos a Query que realiza a Busca na Tabaelas de Imagens
	 * Treinadas, futuramente considerando Relacionadas */
	try {
		/* Parte do MySQL */
		/* Realiza a Conexao com o DB */
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da conexao com o schema definido no Header */

		aux.clear();
		for (i = 0; i < tags.getSize(); i++)
			aux += i;

		str.clear();
		str.append("(Select t0.Id From IMG_TREINADA t0 ");
		if(tags.getSize() > 1)	str.append(inner_join(tags, aux));
		str.append("Where (");

		/* Trata das clausulas Where */
		for (i = 0; i < tags.getSize(); i++) {
			str.append("t");
			str.append(aux.getIWord(i));
			str.append(".Tag = '");

			str.append(tags.getIWord(i));
			str.append("'");

			if ((i + 1) != tags.getSize()) {
				str.append(" AND ");
			}
		}
		str.append(") Order By t0.Contador DESC)");
		/* Termina de montar a Query de Busca! */

		stmt = con->createStatement();
		res = stmt->executeQuery(str);

		while (res->next()) {
			count++;
			asw += res->getInt("Id");
		}

		/* Se ja achou um resultado bom de pesquisa */
		if (count >= 20) {
			asw.no_repeat();
		cout << setw (10);
			cout << asw;
			return 0;
		}

		/* Resultados insulficientes! Procura na tabela geral */
		str.append(" UNION (Select Id From TABIMG Where ");
		for (i = 0; i < tags.getSize(); i++) {
			str.append("Tags Like \"% ");
			str.append(tags.getIWord(i));
			str.append(" %\"");
			str.append(" AND ");
		}

		str.append("Exists (Select Id From IMG_TREINADA Where ");
		for (i = 0; i < tags.getSize(); i++) {
			str.append("Tag = '");
			str.append(tags.getIWord(i));
			str.append("'");

			if (i + 1 != tags.getSize())
				str.append(" OR ");
		}
		str.append("))");

		/* Colhe o resultado da Query */
		count = 0;
		while (res->next()) {
			count++;
			asw += res->getInt("Id");
		}

		if (count >= 20) {
			asw.no_repeat();
		cout << setw (10);
			cout << asw;
			return 0;
		}

		/* Pior dos Casos! */
		str.append(" UNION (Select Id From TABIMG Where ");
		for (i = 0; i < tags.getSize(); i++) {
			str.append("Tags Like \"% ");
			str.append(tags.getIWord(i));
			str.append(" %\"");

			if (i + 1 != tags.getSize())
				str.append(" AND ");
		}

		str.append(")");
		res = stmt->executeQuery(str);

		/* Colhe o resultado da Query */
		count = 0;
		while (res->next()) {
			count++;
			asw += res->getInt("Id");
		}

		asw.no_repeat();
		cout << setw (10);
		cout << asw;
		return 0;

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return 0;
}
/* ------------------------------------------------------------------------- */
string inner_join(Text tags, Text aux) {
	size_t i;	string tmp;

	tmp = "INNER JOIN (";
	for (i=1; i<aux.getSize(); i++) {
		tmp.append("IMG_TREINADA t");
		tmp.append(aux.getIWord(i));
		if(i+1 != aux.getSize())	tmp.append(", ");
	}

	tmp.append(") ON (");

	for (i=1; i<aux.getSize(); i++) {
		tmp.append("t0.Id = t");
		tmp.append(aux.getIWord(i));
		tmp.append(".Id");
		if(i+1 != aux.getSize())	tmp.append(" AND ");
	}
	tmp.append(") ");

	return tmp;
}
