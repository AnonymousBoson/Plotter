CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags --glibs`
ROOFITFLAGS = -lRooFit -lRooFitCore

all:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

DrawMC:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc

fitMgg:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

clean:
	rm DrawMC.exe fitMgg.exe
