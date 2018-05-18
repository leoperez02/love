/*
 * alienTx.c
 * 
 * Copyright 2018 Lain Iwakura <lain@pavilion>
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

#include "alienTx_fun.h"

int sockfd;
unsigned char buffer[MTU];

/*
 * 
 * name: transfer_file
 * @param src_file cadena de la ruta y nombre del archivo a enviar
 * @param ip_address cadena de la direccion IP del servidor
 * @param dest_path ruta de destino o ruta ded destino y nombre del 
 * nuevo archivo en el servidor. NULL en caso de usar la ruta default
 * y el mismo nombre de archivo
 * 
 */
void transfer_file(char *src_file, char *ip_address, char *dest_path)
{	
	FILE *file;
	int bytes, bytes_writed, bytes_readed, NUM_BYTES;
	char *file_name, *transfer_path;
	/**
	 * Crear un socket y conectarse al servidor
	 * */
	printf("Abriendo un socket hacia el servidor %s ...\n",ip_address);
	make_socket(ip_address);
	printf("Socket conectado!\n");
	/*
	 *	Inicia la transferencia de datos entre cliente y servidor
	*/	
	
	/**
	 * Enviar archivo
	 * 
	 * 1. Enviar ruta destino y nombre del archivo destino
	 * 2. Enviar numero de bytes del archivo
	 * 3. Enviar contenido del archivo
	 * */
	
	/**
	 * 1. Enviar ruta y nombre
	 * */
	//if ( dest_path != NULL ) //Se envia la ruta destino del archivo 
	//{
		///*
		 //* Para verificar si se trata de la ruta destino y el nombre
		 //* nuevo del archivo o solamente de la ruta, se evalua el ultimo
		 //* caracter de la cadena y se compara con la diagonal '/'
		 //* */
		//if ( dest_path[strlen( dest_path ) - 1] == '/') // Es ruta
		//{
			//// Se obtiene el nombre original del archivo sin ruta
			//file_name = get_file_name(src_file); 
			////printf("Nombre de archivo destino: %s\n",file_name);
			//// Se concatena el nombre original a la ruta destino
			//transfer_path = get_path_file(dest_path, file_name);
		//}
		//else // Es ruta y nombre del destino
		//{
			//transfer_path = dest_path;
		//}
	//}
	//else // Se usa la ruta default ./ con el nombre del archivo original
	//{
		//// Se obtiene el nombre original del archivo sin ruta
		//file_name = get_file_name(src_file); 
		////printf("Nombre de archivo: %s\n",file_name);
		///*
		//for(int i = 0 ; i<strlen(file_name)+1 ; i++)
			//printf("%c=%d\n",file_name[i],file_name[i]);
		//printf("concat\n");
		//*/
		//transfer_path = get_path_file("./", file_name);
		///*
		//for(int i = 0 ; i<strlen(transfer_path)+1 ; i++)
			//printf("%c=%d\n",transfer_path[i],transfer_path[i]);
		//*/
	//}
	printf("Cadena enviada al servidor: %s\n",src_file);
	bytes_writed = send_data(src_file);
	/**
	* Esperar respuesta del servidor, regresa la ruta de destino 
	* */
	bytes_readed = get_data();
	/*
	if( bytes_readed != bytes_writed )
	{
		perror("Fallo la transmision de la ruta de destino\n");
		exit(1);
	}
	* 
	* */
	printf(" %d bytes leidos del stream\n",bytes_readed); 
	file_name = get_mem(bytes_readed);
	printf("Respueesta del servidor: %s\n",file_name);
	//se omite comprobacion buffer == transfer_path
	
	///**
	 //* 2. Enviar numero de bytes del archivo
	 //* */
	//char *command1 = "ls -l ";
	//char *command2 = " | cut -d ' ' -f 5 > tam.tmp" ;
	//char *c1 = get_path_file(command1,src_file);
	//char *c2 = get_path_file(c1,command2);
	//system(c2);
	//file = fopen("tam.tmp","r");
	//fgets(buffer,16,file);
	//bytes_writed = send_data(buffer);
	//fclose(file);
	//NUM_BYTES = atoi(buffer);
	//system("rm tam.tmp");
	
	///**
	 //* 3. Enviar bytes del archivo
	 //* */
	///**
	 //* Abrir archivo a transferir en modo binario de lectura
	 //* */
	//file = fopen(src_file,"rb");
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
		//bytes_writed = write(sockfd, &buffer, bytes_readed); 
		//if( bytes_writed < 0 )
		//{
			//perror("Ocurrio un problema en el envio del mensaje\n");
			//exit(1);
		//}
		//bytes+=bytes_writed; // Cuenta total de bytes transferidos
		//printf("Enviados %d bytes del archivo\n",bytes);
		//bytes_readed = fread(&buffer, sizeof(unsigned char), MTU, file);
		//gotoxy(1,5);
	//}
	//fclose(file);
	
	//printf("\nArchivo enviado!\n");
	///**
	 //* El servidor procesa la imagen y envia el archivo procesado de 
	 //* regreso al cliente
	 //* 
	 //* 1. Recibir ruta destino
	 //* 2. Recibir imagen procesada
	 //* */
	
	///*
	 //* 1. Recibir la cadena de ruta y nombre
	 //* */
	
	//printf("Esperando recibir ruta destino...\n"); 
	//bytes_readed = read(sockfd, &buffer, MTU);
	////printf(" %d bytes leidos del stream\n",bytes_readed); 
	//file_name = get_mem(bytes_readed);
	//printf("Preparando destino %s de la imagen procesada...\n",file_name);
	
	///**
	 //* Creando archivo binario para escritura
	 //* */
	//file = fopen(file_name,"wb");
	///**
	 //* Verificar que no hay error en la apertura
	 //* */
	//if( !file )
	//{
		//perror("Ocurrio un error al crear el archivo");
		//exit(EXIT_FAILURE);
	//}
	
	///*
	 //* Recibir el contenido del archivo procesado
	 //* */
	///**
	 //* Recibir bytes ...
	 //* */
	//printf("Recibiendo archivo ...\n");
	
	//bytes=0;
	//bytes_readed = 0;
	//bytes_writed = 0 ;
	
	//do
	//{	
		//bytes_readed = read (sockfd, &buffer, MTU); 
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
		//gotoxy(1,10);
		
	//}
	//while( bytes < NUM_BYTES);
	
	////	Cerrar descriptor de archivo
	//fclose(file);
	
	//gotoxy(1,11);
	//printf("Archivo recibido y guardado!\n");
	/*
	*	Cierre de la conexion
	*/
	printf ("Cerrando la aplicacion cliente\n");
	close(sockfd);
}
