#include "./stdinc.h"
const int	PORT = 3490; /*puerto de conexion del server, ahi está escuchando*/
const int	MAXDATASIZE = 100; /*tamanio del buffer de entrada*/

int main(int argc, char *argv[]) {
	char *usage = "Usar:  IP del servidor\n nombre";
	int	sd; //descriptor de archivo... 
	char buf[MAXDATASIZE+1]; //el buffer donde llegan los datos del server
	char *ipServer=argv[1]; //la ip del server
	char *msg = argv[2]; //el Nombre o mensaje 

	if (argc != 3){	
		Fatal(usage);
	}
	sd = conectate(ipServer, PORT);
	int status= enviaMensaje(msg,sd);
	if(status==-1){
		FatalPerror("Fallo el envio del mensaje. DRAMA!");	
	}
	int statusRespuesta=esperaRespuesta(sd,buf);
	if(statusRespuesta==-1)	
		FatalPerror("Fallo la recepción del mensaje. DRAMA!");
	
	printf("Mensaje Recibido del servidor: %s \n",buf);

	close(sd);
	return 0;
}






