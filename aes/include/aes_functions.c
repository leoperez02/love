/*
* file: aes_functions.h
*/
#include<aes_aux_functions.h>
#include<aes_functions.h>

/* CONSTANTES */

/* Number of bytes */
#define Nb 4

/* Number of keys */
#define Nk 4 
 
/* Number of rounds */
#define Nr 10

/* ESTRUCTURAS */



/* PROTOTIPOS DE FUNCIONES */

/*  */
void add_round_key(void) ;

/*  */
void inv_mix_columns(void) ;

/*  */
void inv_shift_rows(void) ;

/*  */
void inv_sub_bytes(void) ;

/*  */
void mix_columns(void) ;

/*  */
void rot_word(void) ;

/*  */
void shift_rows(void) ;

/*  */
void sub_bytes(void) ;

/*  */
void sub_word(void) ;