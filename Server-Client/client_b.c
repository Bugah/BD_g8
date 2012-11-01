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

#include "helper.h"           /*  Our own helper functions  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include <time.h>

/*  Global constants  */

#define MAX_LINE           (360)


/*  Function declarations  */

int ParseCmdLine(int argc, char *argv[], char **szAddress, char **szPort);

double diffclock(clock_t clock1, clock_t clock2);

/*  main()  */

int main(int argc, char *argv[]) {
    /* Auxiliares */
    int i;
    clock_t clock1;
    clock_t clock2;
    
    clock1=clock();
    
    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    char     *szAddress;             /*  Holds remote IP address   */
    char     *szPort;                /*  Holds remote port         */
    char     *endptr;                /*  for strtol()              */


    /*  Get command line arguments  */

    ParseCmdLine(argc, argv, &szAddress, &szPort);


    /*  Set the remote port  */

    port = strtol(szPort, &endptr, 0);
    if ( *endptr ) {
	printf("ECHOCLNT: Invalid port supplied.\n");
	exit(EXIT_FAILURE);
    }
	

    /*  Create the listening socket  */

    if ( (conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
	fprintf(stderr, "ECHOCLNT: Error creating listening socket.\n");
	exit(EXIT_FAILURE);
    }


    /*  Set all bytes in socket address structure to
        zero, and fill in the relevant data members   */

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(port);


    /*  Set the remote IP address  */

    if ( inet_aton(szAddress, &servaddr.sin_addr) <= 0 ) {
	printf("ECHOCLNT: Invalid remote IP address.\n");
	exit(EXIT_FAILURE);
    }

    
    /*  connect() to the remote echo server  */

    if ( connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 ) {
	printf("ECHOCLNT: Error calling connect()\n");
	exit(EXIT_FAILURE);
    }

    /*  Manda arquivo .nor desejado para o servidor */

    //Writeline(conn_s, argv[5], strlen(argv[5]));
    
    /* Copia arg[5] pro Buffer */
    
    for(i=0; i<strlen(argv[5]); i=i+1) {
        buffer[i]=argv[5][i];
    }
    buffer[i]='\n';
    
    Writeline(conn_s, buffer, strlen(buffer));
    
    if(argv[5][0]!='0') {
    
        Readline(conn_s, buffer, MAX_LINE-1);

        char * pch;
        pch = strtok (buffer," ");

        for(i=0;i<20;i=i+1) {

            printf ("%s ",pch);
            pch = strtok (NULL," ");
            printf ("%s ",pch);
            pch = strtok (NULL," ");
            printf ("%s\n",pch);
            pch = strtok (NULL," ");
        }
    }
    
    clock2 = clock();
    double ts = diffclock(clock1, clock2);
    printf("Time Spent: %f\n", ts );
    /*  Output echoed string  */

    return 0;
}


int ParseCmdLine(int argc, char *argv[], char **szAddress, char **szPort) {     

    int n = 1;

    while ( n < 4 ) {
	if ( !strncmp(argv[n], "-a", 2) || !strncmp(argv[n], "-A", 2) ) {
	    *szAddress = argv[++n];
	}
	else if ( !strncmp(argv[n], "-p", 2) || !strncmp(argv[n], "-P", 2) ) {
	    *szPort = argv[++n];
	}
	else if ( !strncmp(argv[n], "-h", 2) || !strncmp(argv[n], "-H", 2) ) {
	    printf("Usage:\n\n");
	    printf("    timeclnt -a (remote IP) -p (remote port)\n\n");
	    exit(EXIT_SUCCESS);
	}
	++n;
    }

    return 0;
}

double diffclock(clock_t clock1, clock_t clock2) // Calcular diferenca de tempo
{
    clock2=clock();
    double diffticks=clock2-clock1;
    double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
    return diffms;
}
