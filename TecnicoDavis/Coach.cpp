/*
 * Coach.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: andre
 */
#include "Text.h"
#include "mysql_header.h"
#include <fstream>
using namespace sql;

/* Faz o Treinamento de Tags para melhorar o resultado de pesquisas */
int main(int argc, char *argv[]) {
	/* Parametros:
	 * argv[0]		:= Nome da Chamada (default)
	 * argv[1] 		:= ID da imagem clicada
	 * argv[2-...]	:= Tag usada */

	size_t i, found; 			// Indices da Imagem
	string str, cmd; 			// string auxiliar | comandos
	vector<size_t> up; 			// Guarda o que tem que atualizar
	Text search, aux, tags; 	// Tags pesquisadas | auxiliar
	ifstream infile; 			// Dicionario de tags

	/* Converte os Argumentos para um objeto Text (facil de manipular */
	for (i = 2; i < argc; i++)
		search += argv[i];

	/* Faz a leitura das Tags */
	infile.open("dicionarioTags.tags");
	if (!infile.is_open()) {
		cout << "Dicionario nao encontrado!" << endl;
		return -1;
	} else {
		getline(infile, str);
		aux = str; // Converte o dicionario de tags
		str.clear(); // Limpa a string
	} /* Termino da leitura de tags */

	/* Limpa o texto digitado na busca */
	search -= (search - aux);
	search.no_repeat();

	/* Parametros corretos */
	try {
		/* Variaveis de conexao */
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::PreparedStatement *pstmt;
		sql::ResultSet *res;

		/* Conecta com o DB */
		driver = sql::mysql::get_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da conexao ao schema definido no header */

		cmd.clear(); // Limpa antes de usar
		cmd.append("Insert Into IMG_TREINADA(Id, Tag, Contador) ");
		cmd.append("Values (?,?,?)");

		/* Arruma os Statements */
		stmt = con->createStatement();
		pstmt = con->prepareStatement(cmd);

		/* Executa o comando */
		cmd.clear();
		cmd.append("Select * From IMG_TREINADA WHERE Id = ");
		cmd.append(argv[1]);

		res = stmt->executeQuery(cmd);

		/* Pega para quais tags a imagem de Id especificado
		 * foi treinada para responder */
		aux.clear();
		while (res->next()) {
			str = res->getString("Tag");
			aux += str;
		} /* aux := conjunto de tags para qual imagem(id) foi treinada */

		/* Verifica para todas as tags pesquisadas */
		for (i = 0; i < search.getSize(); i++) {
			/* Fetching Command */
			str = search.getIWord(i);
			found = aux.find_first_of(str);

			/* Achou uma tupla com tag que foi procurada */
			if (found != string::npos) {
				/* Incrementa o valor do Contador Inteligente */
				cmd.clear(); // Limpa a String
				cmd.append("Update IMG_TREINADA ");
				cmd.append("Set Contador = Contador+1 Where Tag = '");
				cmd.append(str);
				cmd.append("' AND Id = ");
				cmd.append(argv[1]);

				/* Agora executa o comando pra atualizar */
				stmt->execute(cmd);
			} else { // Não encontrou a tupla que confere
				/* Verifica se a imagem tem a tag em questao */
				cmd = "Select * From TABIMG Where Id = ";
				cmd.append(argv[1]);

				/* Pega todas as tags da Imagem em questao */
				res = stmt->executeQuery(cmd);
				res->next();
				tags = res->getString("Tags");

				found = tags.find_first_of(str);
				if (found != string::npos) {
					/* Encontrou a tag nas tags das imagens
					 * Nesse caso insere a tupla nas TAGs treinadas */
					pstmt->setInt(1, atoi(argv[1]));
					pstmt->setString(2, str);
					pstmt->setInt(3, 1);
					pstmt->execute();
				} /* Fim da insercao */
				/* Se a tag nao era da imagem nao insere nada */
			} /* Fim de Fetching */
		}

		/* Deleta os objetos do MySQL */
		delete res;
		delete pstmt;
		delete stmt;
		delete con;
	} catch (sql::SQLException &e) { // Para encontrar erros!
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
