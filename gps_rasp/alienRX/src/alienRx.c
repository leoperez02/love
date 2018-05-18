/*
 * alienRx.c
 * 
 * Copyright 2018 Leo <leo@Inspiron3437>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "alienRx_fun.h"
#include "imagen_fun.h"
#include "serial.h"
#include <pthread.h>

int sockfd, cliente_sockfd;
unsigned char buffer[MTU];

void read_client(void);

void* read_gps(void*);
void* run_server(void*);

/**
 * Distintas cadenas recibidas por el GPS 
$GPRMC,,V,,,,,,,,,,N*53
$GPVTG,,,,,,,,,N*30
$GPGGA,,,,,,0,00,99.99,,,,,,*48
$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30
$GPGSV,2,1,05,10,,,22,20,,,22,23,,,22,25,,,22*7A
$GPGSV,2,2,05,32,,,25*7A
$GPGLL,,,,,,V,N*64
 *
*/

char *rmc_string;
char *vtg_string;
char *gga_string;
char *gsa_string;
char *gsv_string;
char *gll_string;

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

/**
 * MAIN
 * */
void start_server(void)
{
   	/**
	 * El flujo del progrmama del servidor se divide en dos hilos:
	 * 
	 * 1. El primer hilo se dedica a leer de manera continua la informacion del
	 * modulo GPS y asi tener actualizadas las variables globales de los
	 * datos GPS
	 * 
	 * 2. El segundo hilo ejecuta el servidor como tal: el proceso padre
	 * espera que se conecten clientes y una vez conectado un cliente, 
	 * crea un proceso hijo para atenderlo, enviando al cliente la
	 * informacion disponible del GPS inmediatamente
	 * */
	
	pthread_t tid_gps, tid_server;
	int *res_gps, *res_server;
	
	/* Inicializacion del mutex*/
	pthread_mutex_init( &bloqueo, NULL);
	
	/* Crear hilo con atributos default */
	pthread_create(&tid_gps, NULL, read_gps, 	NULL);
	pthread_create(&tid_server, NULL, run_server, 	NULL);

	/* Recibir los datos luego de que los hilos terminan */
	pthread_join(tid_gps,  (void**)&res_gps);
	pthread_join(tid_server, (void**)&res_server);
	
	printf("Resultado del hilo es ID = %d\n", *res_gps);
	printf("Resultado del hilo es ID = %d\n", *res_server);	
	
	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );
}

void read_client(void)
{
	/*
	* Inicia la transferencia de datos entre cliente y servidor
	*/
	FILE *file;
	int bytes_readed, bytes_writed, bytes;
	char *file_name, *ruta_destino, *path_file;
	
	/**
	 * 1. Recibir cadena solicitada por el cliente
	 * */
	printf("Esperando cadena de info... ");			
	bytes_readed = get_data();
	printf("leidos %d bytes del stream\n",bytes_readed);
	/**
	 * Reservar memoria para la cadena del nombre de archivo
	 * y colocar el contenido del buffer en la memoria
	 * */
	path_file = get_mem(bytes_readed);
	printf("Cadena recibida: %s\n",path_file);
	
	/**
	 * Buscar la cadena y formatearla
	 * */
	// Seleccionar el tipo de comando NMEA
	switch (path_file[2])
	{
		/**
		 * COMANDOS VALIDOS
		 * RMC
		 * VTG
		 * GSV
		 * GLL
		 * GSA
		 * GGA
		 * */
		case 'C':
			path_file = rmc_string;
		break;
		
		case 'G':
			path_file = vtg_string;
		break;
		
		case 'V':
			path_file = gsv_string;
		break;
		
		case 'L':
			path_file = gll_string;
		break;
		
		case 'A': // peude ser GSA o GGA
			if( path_file[1] == 'S')
			{
				path_file = gsa_string;
			}
			else
			{
				path_file = gga_string;
			}
		break;
		
		default:
			path_file = "ERROR 404";
		break;
	}
	 
	/**
	 * Enviar de vuelta la info
	 * */
	bytes_writed = write (cliente_sockfd, path_file, strlen(path_file)); 
	/*
	if ( bytes_writed != strlen(path_file))
	{
		perror("No se escribio correctamente el nombre de archivo\n");
		exit(1);
	}
	*/
	///* 
	 //* 2. Recibir el numero de bytes del archivo
	 //* */
	//bytes_readed = get_data();
	//char *num_bytes = get_mem(bytes_readed);
	//int NUM_BYTES = atoi(num_bytes);
	
	///**
	 //* 3. Recibiendo los bytes del archivo
	 //* */ 
	//printf("Creando archivo %s\n",path_file);
	///**
	//* Crear archivo binario para escritura
	//* */
	//file = fopen(path_file,"wb");
	///**
	//* Verificar que no hay error en la apertura
	//* */
	//if(!file)
	//{
		//perror ("Ocurrio un problema al abrir el archivo\n");
		//exit(1);
	//}
	///**
	 //* Recibir bytes ...
	 //* */
	//printf("Recibiendo archivo ...\n");
	
	//bytes=0;
	//bytes_readed = 0;
	//bytes_writed = 0 ;
	
	//do
	//{	
		//bytes_readed = read (cliente_sockfd, &buffer, MTU); 
		//if( bytes_readed < 0 )
		//{
			//perror ("Ocurrio algun problema al recibir datos del cliente");
			//exit(1);
		//}
		//bytes_writed = fwrite(&buffer, sizeof(unsigned char), bytes_readed, file);
		//if( bytes_writed < 0 )
		//{
			//perror("Error al leer el stream de datos\n");
		//}
		//bytes+=bytes_readed;
		//printf("Recibidos %d bytes del archivo\n",bytes);
		//gotoxy(1,9);
	//}
	//while( bytes < NUM_BYTES);
	
	////	Cerrar descriptor de archivo
	//fclose(file);
	//gotoxy(1,10);
	//printf("Archivo recibido y guardado!\n");
	
	///**
	 //* Inicia procesamiento de la imagen recibida
	 //* 
	 //* La función get_bordes() recibe la ruta del archivo de 
	 //* imagen a procesaar y el nombre del archivo nuevo a generar
	 //* */
	//printf("Procesando imagen ... \n");
	//get_bordes(path_file,"build/img_proc.bmp");
	//printf("Imagen lista!. Enviando de vuelta ... \n");
	
	///**
	 //* Devolver la imagen procesada al cliente
	 //* 
	 //* 1. Se envia la ruta y nombre destino de la imagen procesada 
	 //* 2. Se envia el contenido de la imagen
	 //* */
	 
	 //// Enviar ruta
	 
	 //ruta_destino = "./img_proc.bmp" ;
	 //printf("Enviando ruta %s ...\n",ruta_destino);
	 //bytes_writed = write(cliente_sockfd,ruta_destino,MTU);
	 ////printf("%d bytes enviados\n",bytes_writed);
	 //printf("Ruta transmitida!\n");
	  
	//// Enviar imagen
	///**
	 //* Abrir archivo a transferir en modo binario de lectura
	 //* */
	//file = fopen("build/img_proc.bmp","rb");
	///**
	 //* Verificar que no hay error en la apertura
	 //* */
	//if(!file)
	//{
		//perror ("Ocurrio un problema al abrir el archivo\n");
		//exit(1);
	//}
	///**
	 //* Transferir bytes ...
	 //* */
	//printf("Iniciando transferencia...\n");

	//bytes=0; // Contador de los bytes transferidos 
	
	//// Leer MTU bytes del archivo en el buffer para transmitir
	//bytes_readed = fread(&buffer, sizeof(unsigned char), MTU, file);
	//while ( bytes_readed )
	//{
		//// Escribir en el socket los bytes leidos del buffer
		//bytes_writed = write(cliente_sockfd, &buffer, bytes_readed); 
		//if( bytes_writed < 0 )
		//{
			//perror("Ocurrio un problema en el envio del mensaje\n");
			//exit(1);
		//}
		//bytes+=bytes_writed; // Cuenta total de bytes transferidos
		//gotoxy(1,30);
		//printf("Enviados %d bytes del archivo\n",bytes);
		//bytes_readed = fread(&buffer, sizeof(unsigned char), MTU, file);
	//}
	//fclose(file);
	
	//printf("\nArchivo enviado!\n");
	 
	/**
	 * Para finalizar correctamente el proceso hijo, debe 
	 * enviarse una señal al proceso padre que avise que el 
	 * proceso hijo ha finalizado.
	 * 
	 * La señal funciona como una interrupcion en el proceso 
	 * padre para que no hacer el proceso bloqueante 
	 * */
	close (cliente_sockfd); // Cerrar socket cliente
	kill( getppid(), SIGUSR1 );
	exit(EXIT_SUCCESS);
}


void* read_gps(void* arg)
{
	register int i;
	register int count;
	int fd_serie;
	char dato;
	char buffer[1000];
	
	// Abrir comunicacion serial
	fd_serie = config_serial( "/dev/ttyACM0", B9600 );
	//printf("Serial abierto con descriptor: %d\n", fd_serie);
	
	// Leer continuamente los datos del GPS
	while(1)
	{
		// Leer n caracteres hasta salto de linea y guardar la cadena
		count = 0 ;
		do
		{
			read ( fd_serie, &dato, 1 );
			buffer[count] = dato;
			count ++;
		}
		while ( dato != '\n');
		
		
		/* Seccion critica del hilo */
		pthread_mutex_lock( &bloqueo );
		
		// Seleccionar el tipo de comando NMEA
		switch (buffer[5])
		{
			case 'C':
				// Reservar memoria para count caracteres
				rmc_string = (char *) malloc (sizeof(char)*count);
				for (i = 0 ; i < count ; i++)
				{
					rmc_string[i] = buffer[i];
				}

				// Reemplazar salto de linea por caracter de fin de cadena
				rmc_string[count-1] = '\0';	
			break;
			
			case 'G':
				// Reservar memoria para count caracteres
				vtg_string = (char *) malloc (sizeof(char)*count);
				for (i = 0 ; i < count ; i++)
				{
					vtg_string[i] = buffer[i];
				}

				// Reemplazar salto de linea por caracter de fin de cadena
				vtg_string[count-1] = '\0';	
			break;
			
			case 'V':
				// Reservar memoria para count caracteres
				gsv_string = (char *) malloc (sizeof(char)*count);
				for (i = 0 ; i < count ; i++)
				{
					gsv_string[i] = buffer[i];
				}

				// Reemplazar salto de linea por caracter de fin de cadena
				gsv_string[count-1] = '\0';	
			break;
			
			case 'L':
				// Reservar memoria para count caracteres
				gll_string = (char *) malloc (sizeof(char)*count);
				for (i = 0 ; i < count ; i++)
				{
					gll_string[i] = buffer[i];
				}

				// Reemplazar salto de linea por caracter de fin de cadena
				gll_string[count-1] = '\0';	
			break;
			
			case 'A': // peude ser GSA o GGA
				if( buffer[4] == 'S')
				{
					// Reservar memoria para count caracteres
					gsa_string = (char *) malloc (sizeof(char)*count);
					for (i = 0 ; i < count ; i++)
					{
						gsa_string[i] = buffer[i];
					}

					// Reemplazar salto de linea por caracter de fin de cadena
					gsa_string[count-1] = '\0';
				}
				else
				{
					// Reservar memoria para count caracteres
					gga_string = (char *) malloc (sizeof(char)*count);
					for (i = 0 ; i < count ; i++)
					{
						gga_string[i] = buffer[i];
					}

					// Reemplazar salto de linea por caracter de fin de cadena
					gga_string[count-1] = '\0';
				}
			break;
			
			default:
			break;
		}
		
		/* Fin seccion critica*/
		pthread_mutex_unlock( &bloqueo );
	}
	// Cerrar descriptor de archivo y salir del hilo
	close(fd_serie);
	pthread_exit( arg );
}

void* run_server(void* arg)
{
	/* TEST 
 	char c;
	while(1)
	{
		//printf("\nTeclea para recibir datos del gps: ");
		//scanf("%c",&c);
		printf("GPS:\n%s\n",rmc_string);
		printf("GPS:\n%s\n",vtg_string);
		printf("GPS:\n%s\n",gga_string);
		printf("GPS:\n%s\n",gsa_string);
		printf("GPS:\n%s\n",gsv_string);
		printf("GPS:\n%s\n",gll_string);
	}
	*/
	
	//Estructura de la familia AF_INET, que almacena direccion
   	struct sockaddr_in direccion_servidor; 
   	
   	/**
   	 * Colocando señal SIGUSR1 para escuchar por el procso padre
   	 * */
   	if ( signal( SIGUSR1, isr_signal) == SIG_ERR ) 
	{
		perror("Error en señal\n");
		exit(EXIT_FAILURE);
	}
	
	/*	
	 *	AF_INET - Protocolo de internet IPV4
	 *  htons - El ordenamiento de bytes en la red es siempre big-endian, 
	 * 	por lo que en arquitecturas little-endian se deben revertir los 
	 * 	bytes
	 *  INADDR_ANY - Se elige cualquier interfaz de entrada
	 */	
	//se limpia la estructura con ceros
   	memset (&direccion_servidor, 0, sizeof (direccion_servidor));	
   	direccion_servidor.sin_family 		= AF_INET;
   	direccion_servidor.sin_port 		= htons(PUERTO);
   	direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;

	/*
	 *	Creacion de las estructuras necesarias para el manejo de un 
	 * 	socket
	 *  SOCK_STREAM - Protocolo orientado a conexión
	 */
	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}
	/*
	 *  bind - Se utiliza para unir un socket con una dirección de red
	 *  determinada
	 */
	//printf("Configurando socket ...\n");
	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
	{
		perror ("Ocurrio un problema al configurar el socket");
		exit(1);
	}
	/*
	 *  listen - Marca al socket indicado por sockfd como un socket 
	 * 	pasivo, esto es, como un socket que será usado para aceptar 
	 * 	solicitudes de conexiones de entrada usando "accept"
	 *  Habilita una cola asociada la socket para alojar peticiones de 
	 * 	conector procedentes de los procesos clientes
	 */
	//printf ("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 )
	{
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
	}
	/*
	 *  accept - Aceptación de una conexión
	 *  Selecciona un cliente de la cola de conexiones establecidas
	 *  se crea un nuevo descriptor de socket para el manejo
	 *  de la nueva conexion. Apartir de este punto se debe
	 *  utilizar el nuevo descriptor de socket
	 *  accept - ES BLOQUEANTE 
	 */

	while(1)
	{
		printf ("En espera de peticiones de conexión ...\n");
		if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 )
		{
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
		}
	
		pid_t pid = fork();
		if( !pid ) /* proceso hijo*/
		{
			printf("Se acepto un cliente, atendiendolo... \n");
			read_client();
		}
		//printf("Concluimos la ejecución de la aplicacion Servidor \n");
	}
	/*
	 *	Cierre de las conexiones
	 */
	close (sockfd);
	pthread_exit( arg );
}


