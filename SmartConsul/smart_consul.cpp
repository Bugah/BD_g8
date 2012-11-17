/*
 * main.cpp
 * Created 		on: Oct 29, 2012
 * Last Changed on: Oct 30, 2012
 * Author: andre
 */

#include <fstream>
#include <stdlib.h>
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
	size_t i, j, count = 0;
	string str, tmp; // Retiram os valores no arquivo
	//vector<string> anin; // Aninhamento de Tags
	Text tags, aux, dicio, asw; // Tags retiradas do texto

	// Arquivos de Entrada e Saida
	ifstream infile; // Arquivo com dicionario de Tags
	ofstream outfile("Results.txt"); // Impressao de Resultados

	/* Objetos MySQL */
	sql::mysql::MySQL_Driver * driver;
	sql::Connection * con;
	sql::Statement * stmt;
	sql::ResultSet * res;
	/* Fim das Declaracoes */

	/* Faz a conversao do texto digitado para objetos texto */
	for (i = 1; i < (size_t) argc; i++)
		tags += argv[i];

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
	//anin = permrep(tags.getSize() - 1, anin.size(), anin);
	/* Fim da Inicializacao do Aninhamento */

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
		for (i = 0; i < tags.getSize(); i++)	{
			aux += i;
			cout << aux.getIWord(i) << endl;
		}

		str.clear();
		str.append("(Select * From IMG_TREINADA t0 ");
		if(tags.getSize() > 1)	str.append(inner_join(tags, aux));

		/* Trata das clausulas Where */
		for (i = 0; i < tags.getSize(); i++) {
			str.append("Where (");
			str.append("t");
			str.append(aux.getIWord(i));
			str.append(".Tag = '");

			str.append(tags.getIWord(i));
			str.append("'");

			if ((i + 1) != tags.getSize()) {
				str.append(" AND ");
			}
		}
		str.append(") Order By Contador DESC)");
		/* Termina de montar a Query de Busca! */

		/* Imprimi a Query para buscar as tags principais aninhadas
		cout << str << endl;
		cout << endl;
		*/

		stmt = con->createStatement();
		res = stmt->executeQuery(str);

		while (res->next()) {
			count++;
			asw += res->getInt("Id");
		}

		/* Se ja achou um resultado bom de pesquisa */
		if (count >= 20) {
			asw.no_repeat();
			cout << asw << endl;
			return 0;
		}

		/* Resultados insulficientes! Procura na tabela geral */
		str.append(" UNION (Select * From TABIMG Where ");
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

		/* Imprimi a Query
		cout << str << endl;
		res = stmt->executeQuery(str);

		/* Colhe o resultado da Query */
		count = 0;
		while (res->next()) {
			count++;
			asw += res->getInt("Id");
		}

		if (count > 20) {
			asw.no_repeat();
			cout << asw << endl;
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
		cout << asw << endl;
		return 0;

		/* Se chegou aqui e ainda deu pau... Bom, chora!
		   Por enquanto...
		/* Arruma a Pega as Tags Relacionadas */
		/*
		 for (i = 0; i < tags.getSize(); i++) {
		 /* str: contem a query final
		 * tmp: serve como peao, seu resultado final nao interessa
		 *
		 tmp = "SELECT relacionadas FROM TAGS_RELACIONADAS "
		 "WHERE tag LIKE \"%";

		 tmp.append(tags.getIWord(i));
		 tmp.append("%\"");

		 /* Executa o Select no DB e se prepara para Buscar os resultados
		 stmt = con->createStatement();
		 res = stmt->executeQuery(tmp);

		 /* Transforma a string com as tags relacionadas em objetos Texto
		 res->next();
		 aux = res->getString("relacionadas");

		 /* Limpa o conteudo do vetor de aninhamento inicial
		 //anin.clear();
		 //anin.push_back("AND");
		 tmp.clear();
		 for (j = 0; j < aux.getSize() - 1; j++)
		 tmp.append("OR ");

		 //anin.push_back(tmp);

		 /* Precisamos reiniciar o vetor de aninhamento
		 //anin = permrep(aux.getSize()-1, anin.size(), anin);
		 //str.append(getcmd(anin, aux));
		 if (i + 1 != tags.getSize())
		 str.append(" UNION ");
		 }
		 */
	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	/* Imprime a Query das Relacionadas */
	cout << str << endl;

	return 0;
}
/* ------------------------------------------------------------------------- */
string inner_join(Text tags, Text aux) {
	size_t i;	string tmp;

	tmp = "INNER JOIN (";
	for (i=1; i<aux.getSize(); i++) {
		tmp.append("IMG_TREINADA t");
		tmp.append(aux.getIWord(i));
		if(i+1 != aux.getSize())	tmp.append(" ");
	}

	tmp.append(" ON (");

	for (i=1; i<aux.getSize(); i++) {
		tmp.append("t0.Id = t");
		tmp.append(aux.getIWord(i));
		tmp.append(".Id");
		if(i+1 != aux.getSize())	tmp.append(" AND ");
	}
	tmp.append(") ");

	return tmp;
}
