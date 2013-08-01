CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags --glibs`

all: DrawMC.exe

DrawMC.exe: DrawMC.cc SampleHandler.h
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc

clean:
	rm *.exe
