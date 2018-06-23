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

int sockfd, cliente_sockfd;
unsigned char buffer[MTU];

void read_client(void);

void start_server(void)
{
   	//Estructura de la familia AF_INET, que almacena direccion
   	struct sockaddr_in direccion_servidor; 
   	
   	/**
   	 * Colocando señal SIGUSR1 para escuchar por el procso padre
   	 * */
   	if ( signal( SIGUSR1, isr_signal) == SIG_ERR ) 
	{
		syslog(LOG_ERR,"Error en señal\n");
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
	syslog(LOG_INFO,"Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		syslog(LOG_ERR,"Ocurrio un problema en la creacion del socket");
		exit(1);
	}
	/*
	 *  bind - Se utiliza para unir un socket con una dirección de red
	 *  determinada
	 */
	//printf("Configurando socket ...\n");
	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
	{
		syslog(LOG_ERR,"Ocurrio un problema al configurar el socket");
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
		syslog(LOG_ERR,"Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
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
		syslog(LOG_INFO,"En espera de peticiones de conexión ...\n");
		if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 )
		{
			syslog(LOG_ERR,"Ocurrio algun problema al atender a un cliente");
			exit(1);
		}
	
		pid_t pid = fork();
		if( !pid ) /* proceso hijo*/
		{
			syslog(LOG_INFO,"Se acepto un cliente, atendiendolo... \n");
			read_client();
		}
		//printf("Concluimos la ejecución de la aplicacion Servidor \n");
	}
	/*
	 *	Cierre de las conexiones
	 */
	close (sockfd);
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
	 * Recibir archivo
	 * 
	 * 1. Recibir ruta donde guardar el archivo con nombre
	 * 2. Recibir cantidad de bytes del archivo
	 * 3. Recibir contenido del archivo
	 * */
	
	/**
	 * 1. Recibir nombre del archivo
	 * */
	syslog(LOG_INFO,"Esperando ruta y nombre destino... ");			
	bytes_readed = get_data();
	syslog(LOG_INFO,"leidos %d bytes del stream\n",bytes_readed);
	/**
	 * Reservar memoria para la cadena del nombre de archivo
	 * y colocar el contenido del buffer en la memoria
	 * */
	path_file = get_mem(bytes_readed);
	syslog(LOG_INFO,"Destino recibido: %s\n",path_file);
	/**
	 * Enviar de vuelta el nombre para confirmar
	 * */
	bytes_writed = write (cliente_sockfd, path_file, strlen(path_file)); 
	if ( bytes_writed != strlen(path_file))
	{
		syslog(LOG_ERR,"No se escribio correctamente el nombre de archivo\n");
		exit(1);
	}
	
	/**
	 * 2. Recibir el numero de bytes del archivo
	 * */
	bytes_readed = get_data();
	char *num_bytes = get_mem(bytes_readed);
	int NUM_BYTES = atoi(num_bytes);
	
	/**
	 * 3. Recibiendo los bytes del archivo
	 * */ 
	syslog(LOG_INFO,"Creando archivo %s\n",path_file);
	/**
	* Crear archivo binario para escritura
	* */
	file = fopen(path_file,"wb");
	/**
	* Verificar que no hay error en la apertura
	* */
	if(!file)
	{
		syslog(LOG_ERR,"Ocurrio un problema al abrir el archivo\n");
		exit(1);
	}
	/**
	 * Recibir bytes ...
	 * */
	syslog(LOG_INFO,"Recibiendo archivo ...\n");
	
	bytes=0;
	bytes_readed = 0;
	bytes_writed = 0 ;
	
	do
	{	
		bytes_readed = read (cliente_sockfd, &buffer, MTU); 
		if( bytes_readed < 0 )
		{
			syslog(LOG_ERR,"Ocurrio algun problema al recibir datos del cliente");
			exit(1);
		}
		bytes_writed = fwrite(&buffer, sizeof(unsigned char), bytes_readed, file);
		if( bytes_writed < 0 )
		{
			syslog(LOG_ERR,"Error al leer el stream de datos\n");
		}
		bytes+=bytes_readed;
		syslog(LOG_INFO,"Recibidos %d bytes del archivo\n",bytes);
		//gotoxy(1,9);
	}
	while( bytes < NUM_BYTES);
	
	//	Cerrar descriptor de archivo
	fclose(file);
	//gotoxy(1,10);
	syslog(LOG_INFO,"Archivo recibido y guardado!\n");
	
	/**
	 * Inicia procesamiento de la imagen recibida
	 * 
	 * La función get_bordes() recibe la ruta del archivo de 
	 * imagen a procesaar y el nombre del archivo nuevo a generar
	 * */
	syslog(LOG_INFO,"Procesando imagen ... \n");
	get_bordes(path_file,"./img_proc.bmp");
	syslog(LOG_INFO,"Imagen lista!. Enviando de vuelta ... \n");
	
	/**
	 * Devolver la imagen procesada al cliente
	 * 
	 * 1. Se envia la ruta y nombre destino de la imagen procesada 
	 * 2. Se envia el contenido de la imagen
	 * */
	 
	 // Enviar ruta
	 
	 ruta_destino = "./img_proc.bmp" ;
	 syslog(LOG_INFO,"Enviando ruta %s ...\n",ruta_destino);
	 bytes_writed = write(cliente_sockfd,ruta_destino,MTU);
	 //printf("%d bytes enviados\n",bytes_writed);
	 syslog(LOG_INFO,"Ruta transmitida!\n");
	  
	// Enviar imagen
	/**
	 * Abrir archivo a transferir en modo binario de lectura
	 * */
	file = fopen("./img_proc.bmp","rb");
	/**
	 * Verificar que no hay error en la apertura
	 * */
	if(!file)
	{
		syslog(LOG_ERR,"Ocurrio un problema al abrir el archivo\n");
		exit(1);
	}
	/**
	 * Transferir bytes ...
	 * */
	syslog(LOG_INFO,"Iniciando transferencia...\n");

	bytes=0; // Contador de los bytes transferidos 
	
	// Leer MTU bytes del archivo en el buffer para transmitir
	bytes_readed = fread(&buffer, sizeof(unsigned char), MTU, file);
	while ( bytes_readed )
	{
		// Escribir en el socket los bytes leidos del buffer
		bytes_writed = write(cliente_sockfd, &buffer, bytes_readed); 
		if( bytes_writed < 0 )
		{
			syslog(LOG_ERR,"Ocurrio un problema en el envio del mensaje\n");
			exit(1);
		}
		bytes+=bytes_writed; // Cuenta total de bytes transferidos
		//gotoxy(1,30);
		syslog(LOG_INFO,"Enviados %d bytes del archivo\n",bytes);
		bytes_readed = fread(&buffer, sizeof(unsigned char), MTU, file);
	}
	fclose(file);
	
	syslog(LOG_INFO,"\nArchivo enviado!\n");
	 
	/**
	 * Para finalizar correctamente el proceso hijo, debe 
	 * enviarse una señal al proceso padre que avise que el 
	 * proceso hijo ha finalizado.
	 * 
	 * La señal funciona como una interrupcion en el proceso 
	 * padre para que no hacer el proceso bloqueante 
	 * */
	close (cliente_sockfd); // Cerrar socket cliente
	syslog(LOG_INFO,"Socket cliente cerrado!");
	kill( getppid(), SIGUSR1 );
	syslog(LOG_INFO,"Proceso hijo terminado!");
	exit(EXIT_SUCCESS);
}
