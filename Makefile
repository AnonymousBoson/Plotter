CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags`
ROOTLIBS	= `root-config --libs --ldflags`
ROOFITLIBS = -lRooFit -lRooFitCore -lMinuit
ROOSTATSFLAGS = -lRooStats 

#all: DrawMC fitMgg sPlot
all: DrawMC fitMgg


SampleHandler.o: SampleHandler.h SampleHandler.cc
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c SampleHandler.cc -o SampleHandler.o

DrawMC.o: DrawMC.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c DrawMC.cc -o DrawMC.o

DrawMC: DrawMC.o SampleHandler.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) DrawMC.o SampleHandler.o -o DrawMC.exe

fitMgg.o: fitMgg.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) $(ROOFITLIBS) $(ROOSTATSFLAGS) -c fitMgg.cc -o fitMgg.o

fitMgg:
	$(CC) $(CCFLAGS) $(ROOFITLIBS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

sPlot:
	$(CC) $(CCFLAGS) $(ROOFITLIBS) $(ROOSTATSFLAGS) -o sPlot.exe $(ROOTFLAGS) sPlot.cc

clean:
	rm *.o
	rm DrawMC.exe fitMgg.exe sPlot.exe
	rm -r DrawMC.exe.dSYM fitMgg.exe.dSYM sPlot.exe.dSYM
