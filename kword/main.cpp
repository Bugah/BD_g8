/* ----------------------------------------------------------------------------
 * Title: Text.h --------------------------------------------------------------
 * Author: andre --------------------------------------------------------------
 * Created on: Oct 23, 2012 ---------------------------------------------------
 * Last Changed on: Oct 28, 2012 ----------------------------------------------
 * --------------------------------------------------------------------------*/

#include "Text.h"
#include <fstream>

int main(int argc, char *argv[]) {
	string buff, tmp1, tmp2;	ifstream fdicio, fdesc;
	Text desc, dicio, trash;

	// Parametros: Prog | Arquivo de Descricao | Arquivo de Dicionario de Tags
	if(argc != 3) {
		cout << "Erro de Parametros! Por Favor digite o nome dos Arquivos" << endl;
		getline(cin, tmp1);	getline(cin, tmp2);
	}	else {
		tmp1 = argv[1];	// Leu a descricao
		tmp2 = argv[2];
	}

	fdesc.open(tmp1.c_str());	// Abre o Arquivo de Descricao

	// Transforma a descricao em objetos texto
	if(fdesc.is_open()) {
		getline(fdesc, tmp1);
		buff = " ";	buff += tmp1;
		while(!fdesc.eof())	{
			desc += buff;
			desc += " ";
			getline(fdesc, buff);
		}
	} else {
		cout << "Arquivo de Descricao nao Encontrado! Processo Abortado!" <<endl;
		return -1;
	}

	desc.printTxt();
	// Faz a Leitura do dicionario de tags
	fdicio.open(tmp2.c_str());

	// Transforma o dicionario em objetos texto
	if(fdicio.is_open()) {
		getline(fdicio, buff);
		dicio = buff;
	} else {
		cout << "Arquivdo de Dicionario nao Encontrado! Processo Abortado!" << endl;
		return -1;
	}

	// Agora retiramos todas as palavras que nao sao Tags
	trash = desc-dicio;
	trash.printTxt();

	desc -= trash;

	// Agora desc só tem as tags
	desc.printTxt();
	return 0;
}
