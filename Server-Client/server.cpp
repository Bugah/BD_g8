/*
 * Alexandre Luiz Brisighello Filho
  
 * 
 * Usado como Início/Base: 
 * 
  ECHOSERV.C
  ==========
  (c) Paul Griffiths, 1999
  Email: mail@paulgriffiths.net
  Simple TCP/IP echo server.

*/


#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include "helper.h"           /*  our own helper functions  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*  Global constants  */

#define ECHO_PORT          (2002)
#define MAX_LINE           (360)


/* MySQL */

#include <iostream>
#include <cppconn/exception.h>
#include "mysql_header.h"
#include <vector>
#include "Vetorzao.h"
#include "KMaxHeap.h"

#include <sstream>

/* Funções */

void reload();
void compute(const char * norpath, KMaxHeap * Heapzim);


/* Namespaces */

using namespace std;
using namespace sql::mysql;

/* Reset Server */

string command="SELECT * FROM Vectors";       
            
/* Variaveis de coneccao */
sql::mysql::MySQL_Driver *driver;
sql::Connection *con;
sql::PreparedStatement *pstmt;
sql::ResultSet *res;

vector <Vetorzao> cache_ci;
//KMaxHeap Heapzim;

char tryme='a';

int main(int argc, char *argv[]) {
    int       list_s;                /*  listening socket          */
    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    
    char      buffer_t[MAX_LINE];
    
    char     *endptr;                /*  for strtol()              */

    
    string time;

    /*  Get port number from the command line, and
        set to default port if no arguments were supplied  */

    if ( argc == 2 ) {
	port = strtol(argv[1], &endptr, 0);
	if ( *endptr ) {
	    fprintf(stderr, "ECHOSERV: Invalid port number.\n");
	    exit(EXIT_FAILURE);
	}
    }
    else if ( argc < 2 ) {
	port = ECHO_PORT;
    }
    else {
	fprintf(stderr, "ECHOSERV: Invalid arguments.\n");
	exit(EXIT_FAILURE);
    }

	
    /*  Create the listening socket  */

    if ( (list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
	fprintf(stderr, "ECHOSERV: Error creating listening socket.\n");
	exit(EXIT_FAILURE);
    }


    /*  Set all bytes in socket address structure to
        zero, and fill in the relevant data members   */

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);


    /*  Bind our socket addresss to the 
	listening socket, and call listen()  */

    if ( bind(list_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
	fprintf(stderr, "ECHOSERV: Error calling bind()\n");
	exit(EXIT_FAILURE);
    }

    if ( listen(list_s, LISTENQ) < 0 ) {
	fprintf(stderr, "ECHOSERV: Error calling listen()\n");
	exit(EXIT_FAILURE);
    }

    
    reload();   // [Re]Carregamento Inicial
    
    /*  Enter an infinite loop to respond
        to client requests and echo input  */

    while ( 1 ) {
        
        KMaxHeap * heap_p;              // Heap!

	/*  Wait for a connection, then accept() it  */

	if ( (conn_s = accept(list_s, NULL, NULL) ) < 0 ) {
	    fprintf(stderr, "ECHOSERV: Error calling accept()\n");
	    exit(EXIT_FAILURE);
	}

	/*  Retrieve an input line from the connected socket
	    then simply write it back to the same socket.     */
        
	Readline(conn_s, buffer, MAX_LINE-1);           // Espera por Pedido
        
        cout << "Entrada no Server" << endl;

        // Se o primeiro argumento for zero, é pra zerar! :D
        if(buffer[0]!='0') {
        
            heap_p = new KMaxHeap[1];       // Cria Heap
            compute(buffer, heap_p);        // Computa

            (* heap_p).PrintHash();         // Imprimi Resultados
            (* heap_p).Make_Answer(buffer); // Cria resposta (Burocracia)

            Writeline(conn_s, buffer, strlen(buffer));      // Devolve Resposta

            delete[] heap_p;                // Ao acabar, libera Hash.
            /*  Close the connected socket  */
        }
        
        else {
            reload();
        }

	if ( close(conn_s) < 0 ) {
	    fprintf(stderr, "ECHOSERV: Error calling close()\n");
	    exit(EXIT_FAILURE);
	}
    }
}


/* Funcão que efetua toda leitura e guarda no vector cache_si : Rodada apenas no início e quando houver update */
void reload() {
    string initial;
    int indice;
    Vetorzao Vet_t;
    
    driver =sql::mysql::get_driver_instance();
    con = driver->connect(DBHOST, USER, PASSWORD);
    con->setSchema(DATABASE);
    
    pstmt = con->prepareStatement(command);
    res = pstmt->executeQuery();
    
    cache_ci.clear();
    
    int term=0;
    
    while (res->next()) {
        initial = res->getString("Coord");
        indice = res->getInt("Id");
        Vet_t.reset(initial, indice);
        cache_ci.push_back(Vet_t);
        term=term+1;
        cout << "Termo: " << term << endl;
    } 
    
    return;
}

void compute(const char * norpath, KMaxHeap * Heapzim) {
    Vetorzao answer;

    string correct;
    
    correct.clear();
    correct.append(norpath);
    
    correct.resize(correct.size()-1);   // Tira o \n
    
    answer.resetNor(correct.c_str());
    
    answer.normalized_Euclidean_distance(cache_ci, Heapzim);
}