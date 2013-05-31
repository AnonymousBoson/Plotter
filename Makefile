CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags --glibs`

all:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc

DrawMC:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc

clean:
	rm DrawMC.exe
