/*
 * main.cpp
 * Created	on: Oct 29, 2012
 * Last Changed on: Nov 11, 2012
 * Author: andre
 */

#include <fstream>
#include "Text.h"
#include "mysql_header.h"
using namespace sql;

/* Monta a Query e faz o aninhamento das tags, respectivamente */
void sqlCMD(string *, Text, Text);
vector<string> permrep(int, int, vector<string>);
string getcmd(vector<string>, Text);

/**
 * Programa que irá executar todas as querys, utilizando a classe
 * Text como auxiliar para montá-las e adequar o seu resultado
 * OBS: Esta versao ainda nao trata tags relacionadas
 * */

int main(int argc, char * argv[]) {
	/* Declaracoes */
	size_t i, j;
	string str, tmp; // Retiram os valores no arquivo
	vector<string> anin; // Aninhamento de Tags
	Text tags, aux, dicio; // Tags retiradas do texto

	// Arquivos de Entrada e Saida
	ifstream infile; // Arquivo com dicionario de Tags
	//ofstream outfile("Results.txt"); // Impressao de Resultados

	/* Objetos MySQL */
	sql::mysql::MySQL_Driver * driver;
	sql::Connection * con;
	sql::Statement * stmt;
	sql::ResultSet * res;
	/* Fim das Declaracoes */

	/* Primeiro escolhem as 2 Opcoes de combinacoes das Tags */
	anin.push_back("AND");
	anin.push_back("OR");

	/* Faz a conversao do texto digitado para objetos texto */
	for (i = 1; i < argc; i++)	tags += argv[i];

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
	/* Fim da conversao do texto */

	/* Faz a inicializacao do Vector de Aninhamento
	 * Comeca com todos os valores em AND
	 * */
	if (tags.getSize() == 0) {
		cout << "Nenhuma tag encontrada na descricao!" << endl;
		return -1;
	}
	anin = permrep(tags.getSize() - 1, anin.size(), anin);
	/* Fim da Inicializacao do Aninhamento */

	/* Prepara a Query para ser impressa (Por enquanto sem considerar
	 * tags relacionadas */
	str = getcmd(anin, tags);

	/* Imprimi a Query para buscar as tags principais aninhadas */
	cout << str << endl;
	cout << endl;

	

	str.clear(); // Limpa a String
	/* Agora criamos a Query que realiza a Busca com Tags Relacionadas
	 * Futuramente havera aninhamento */
	try {
		/* Parte do MySQL */
		/* Realiza a Conexao com o DB */
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect(DBHOST, USER, PASSWORD);
		con->setSchema(DATABASE);
		/* Fim da conexao com o schema definido no Header */

		/* Arruma a Pega as Tags Relacionadas */
		for (i = 0; i < tags.getSize(); i++) {
			/* str: contem a query final
			 * tmp: serve como peao, seu resultado final nao interessa
			 *  */
			tmp = "SELECT relacionadas FROM TAGS_RELACIONADAS "
					"WHERE tag LIKE \"%";

			tmp.append(tags.getIWord(i));
			tmp.append("%\"");

			/* Executa o Select no DB e se prepara para Buscar os resultados */
			stmt = con->createStatement();
			res = stmt->executeQuery(tmp);

			/* Transforma a string com as tags relacionadas em objetos Texto */
			res->next();
			aux = res->getString("relacionadas");

			/* Limpa o conteudo do vetor de aninhamento inicial */
			anin.clear();
			//anin.push_back("AND");

			tmp.clear();
			for (j = 0; j < aux.getSize() - 1; j++)	tmp.append("OR ");

			anin.push_back(tmp);

			/* Precisamos reiniciar o vetor de aninhamento*/
			//anin = permrep(aux.getSize()-1, anin.size(), anin);
			str.append(getcmd(anin, aux));

			if (i + 1 != tags.getSize())
				str.append(" UNION ");
		}

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
void sqlCMD(string *arg1, Text arg2, Text arg3) {
	/* arg1: string que sera modificada
	 * arg2: objeto Text com as Tags
	 * arg3: objeto Text com a combinacao de ANDs e ORs
	 * */

	size_t i;

	/* Acerta para as primeras size-1 tags */
	for (i = 0; i < arg2.getSize(); i++) {
		arg1->append(" Tags");
		arg1->append(" LIKE ");
		arg1->append(1, '"');
		arg1->append(1, '%');
		arg1->append(arg2.getIWord(i));
		arg1->append(1, '%');
		arg1->append(1, '"');

		/* Se nao for a ultima iteracao */
		if (i + 1 != arg2.getSize())
			arg1->append(arg3.getIWord(i));
	} /* Fim do acerto */

}
/* ------------------------------------------------------------------------- */
vector<string> permrep(int tam, int el, vector<string> vetor) {
	int n = el, r, i, j;

	/* vetor que representara cada permutacao. */
	vector<int> num;
	/* Retorno */
	vector<string> arg; // Retorno
	/* Auxiliar */
	string tmp;

	/* Tamanho do Vetor de Permutacoes */
	r = tam;

	/* Inicializa o Controlador de permutacoes */
	for (i = 0; i < tam + 1; i++)
		num.push_back(0);

	/* Inicio do algoritmo. */
	while (num[r] == 0) {
		for (i = 0; i < n; i++) {
			tmp.clear();
			/* Grava a Permutacao no Auxiliar */
			for (j = 0; j < r; j++) {
				tmp.append(vetor.at(num[j]));
				tmp.append(" ");
			}

			/* Transfere para o Vector */
			arg.push_back(tmp);

			/* incrementa o algarismo menos
			 * significativo. */
			num[0]++;
		}

		/* distribui os vai-uns. */
		for (i = 0; i < r; i++) {
			if (num[i] == n) {
				num[i] = 0;
				num[i + 1]++;
			}
		}
	}

	return arg;
}
/* ------------------------------------------------------------------------- */
string getcmd(vector<string> anin, Text tags) {
	size_t i;
	Text aux;
	string str, tmp;

	for (i = 0; i < anin.size(); i++) {
		tmp.clear();
		// Transforma a combinacao atual em um texto
		aux = anin.at(i);

		str.append("SELECT Nome FROM TABIMG WHERE");
		sqlCMD(&tmp, tags, aux);
		str.append(tmp);

		/* Se nao for a ultima iteracao! */
		if (i + 1 != anin.size())
			str.append(" UNION ");
	}

	return str;
}
