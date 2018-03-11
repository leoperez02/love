#archivo makefile

# Variables generales para el makefile
PROYECTO=main_vector_fun
BIBLIOTECA=libvector_fun.so
DESTDIR=/usr/local/bin
CFLAGS=-Wall -ansi -pedantic -I../../sorts/merge_sort/
LDFLAGS=-lm -L../../sorts/merge_sort/ -lmerge_sort -Wl,-rpath=../../sorts/merge_sort/
CC=gcc

all: $(PROYECTO)

biblio: $(BIBLIOTECA)
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

$(BIBLIOTECA): $(s_files:.c=.o)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# Variables especiales $^ y $@
#	$(CC) $^ -o $(PROYECTO) $(LDFLAGS) 
#	$(CC) procesamiento.o archivos.o muestreo.o -o $(PROYECTO) $(LDFLAGS) 

lib: biblio
	export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)

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
	rm *.o *.so $(PROYECTO)
