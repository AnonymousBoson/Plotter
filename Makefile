CC				= g++
CCFLAGS		=	-Wall -g -arch i386 
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags`
ROOTLIBS	= `root-config --glibs`
ROOFITFLAGS = -lRooFit -lRooFitCore
ROOSTATSFLAGS = -lRooStats 

all: DrawMC fitMgg sPlot

SampleHandler.o: SampleHandler.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c SampleHandler.cc -o SampleHandler.o

DrawMC.o: DrawMC.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c DrawMC.cc -o DrawMC.o

# DrawMC: SampleHandler.o DrawMC.o
# 	$(CC) $(CCFLAGS) $(ROOTFLAGS) $(ROOTLIBS) DrawMC.o SampleHandler.o -o DrawMC.exe

DrawMC: DrawMC.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) $(ROOTFLAGS) DrawMC.o -o DrawMC.exe

fitMgg:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

sPlot:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) $(ROOSTATSFLAGS) -o sPlot.exe $(ROOTFLAGS) sPlot.cc

clean:
	rm *.o
	rm DrawMC.exe fitMgg.exe sPlot.exe
	rm -r DrawMC.exe.dSYM fitMgg.exe.dSYM sPlot.exe.dSYM
