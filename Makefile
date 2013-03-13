CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags`
ROOTLIBS	= `root-config --libs --ldflags`
ROOFITLIBS = -lRooFit -lRooFitCore -lMinuit
ROOSTATSLIBS = -lRooStats 

all: DrawMC fitMgg sPlot
#all: DrawMC fitMgg


SampleHandler.o: SampleHandler.h SampleHandler.cc
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c SampleHandler.cc -o SampleHandler.o

DrawMC.o: DrawMC.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c DrawMC.cc -o DrawMC.o

DrawMC: DrawMC.o SampleHandler.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) DrawMC.o SampleHandler.o -o DrawMC.exe

fitMgg.o: fitMgg.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c fitMgg.cc -o fitMgg.o

fitMgg: fitMgg.o SampleHandler.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) $(ROOFITLIBS) fitMgg.o SampleHandler.o -o fitMgg.exe

sPlot.o: sPlot.cc
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c sPlot.cc -o sPlot.o

sPlot: sPlot.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) $(ROOFITLIBS) $(ROOSTATSLIBS) sPlot.o -o sPlot.exe

clean:
	rm *.o
	rm DrawMC.exe fitMgg.exe sPlot.exe
	rm -r DrawMC.exe.dSYM fitMgg.exe.dSYM sPlot.exe.dSYM
