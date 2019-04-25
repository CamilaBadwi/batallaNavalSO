#include "./stdinc.h"
const int	MYPORT = 3490;	/*cliente se conecta en este puerto*/
const int	BACKLOG = 10;	/*max # conexiones pendientes*/
const int	MAXDATASIZE = 100; /*tamagno del buffer de entrada*/
main() {
	int sd;		/*listen sobre sd*/
	int new_fd;	/*nueva conexion*/ 
	char *msg = "Gracias por tu mensaje.\n";	/*responder msg*/
	char buf[MAXDATASIZE+1]; //buffer.
	int sinSz = sizeof(struct sockaddr_in);	//tamaño de la estructura de entrada (datos del cliente que se conecta) ...
	struct sockaddr_in clAddr;		/*direccion del cliente*/
	sd=conectaServer(MYPORT,BACKLOG);
	if(sd ==-1){
		FatalPerror("NO CONECTO EL SERVER!. DRAMA!");	
	}
	while(1) { // loop principal para el  accept() 
		new_fd = accept(sd, (struct sockaddr *) &clAddr, &sinSz);
		if (new_fd == -1)  
			FatalPerror("accept");
		int statusRespuesta=esperaRespuesta(new_fd,buf);
		if(statusRespuesta==-1)	{
			FatalPerror("Fallo la recepción del mensaje. DRAMA!");
			close(new_fd);
			break;
		}
		printf("SERVIDOR: Obtuvo conexión de: %s, y su nombre es: %s\n",inet_ntoa(clAddr.sin_addr),buf);
		int status=enviaMensaje(msg,new_fd);
		if(status==-1){
			FatalPerror("Fallo el envio del mensaje. DRAMA!");	
		}
		close(new_fd);
	}//fin while
	printf("Apagando el server...");
	close(sd);
}

