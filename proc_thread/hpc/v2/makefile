#archivo makefile

# Variables generales para el makefile
PROYECTO=main_hpc_v2
DESTDIR=/usr/local/bin
CFLAGS=-Wall -ansi -pedantic 
LDFLAGS=-lm -lpthread 
CC=gcc

all: $(PROYECTO)

# Reduccion 1
%.o: %.c
	$(CC) -c $< $(CFLAGS)

# Remplaza a:
#procesamiento.o: procesamiento.c
#	$(CC) -c procesamiento.c $(CFLAGS)

#archivos.o: archivos.c
#	$(CC) -c archivos.c $(CFLAGS)

#muestreo.o: muestreo.c
#	$(CC) -c muestreo.c $(CFLAGS)

# TAREA
# Uso de wildcards

# Anterior
#$(PROYECTO): procesamiento.o archivos.o muestreo.o

# Simplificacion con wildcars y sustitucion de patrones:
# Lista de todos los archivos fuente .c
s_files = $(wildcard *.c)
# Sustitucion de *.c por *.o en la lista de archivos fuente
$(PROYECTO): $(s_files:.c=.o)
	$(CC) $^ -o $@ $(LDFLAGS) 

# Variables especiales $^ y $@
#	$(CC) $^ -o $(PROYECTO) $(LDFLAGS) 
#	$(CC) procesamiento.o archivos.o muestreo.o -o $(PROYECTO) $(LDFLAGS) 

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

# Clean region 4
.PHONY: barrele

barrele:
	rm *.o $(PROYECTO)
