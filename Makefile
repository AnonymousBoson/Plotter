CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags`
ROOTLIBS	= `root-config --libs`
ROOFITFLAGS = -lRooFit -lRooFitCore
ROOSTATSFLAGS = -lRooStats 

all: DrawMC fitMgg sPlot

#SampleHandler.o: SampleHandler.cc SampleHandler.h
#	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c SampleHandler.cc -o SampleHandler.o
SampleHandler.o: SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c SampleHandler.h -o SampleHandler.o

DrawMC.o: DrawMC.cc SampleHandler.h
	$(CC) $(CCFLAGS) $(ROOTFLAGS) -c DrawMC.cc -o DrawMC.o

# DrawMC: SampleHandler.o DrawMC.o
# 	$(CC) $(CCFLAGS) $(ROOTFLAGS) $(ROOTLIBS) DrawMC.o SampleHandler.o -o DrawMC.exe

DrawMC: DrawMC.o
	$(CC) $(CCFLAGS) $(ROOTLIBS) $(ROOTFLAGS) DrawMC.cc SampleHandler.h -o DrawMC.exe

DrawMC2: DrawMC.o SampleHandler.o
	$(CC) $(CCFLAGS) $(ROOTFLAGS) $(ROOTLIBS) SampleHandler.o DrawMC.o -o DrawMC.exe

DrawMC3: DrawMC.o SampleHandler.o
	$(CC) -shared -o $@ `root-config --ldflags` -I$(ROOTSYS)/include $^
	$(CC) $(CCFLAGS) $(ROOTFLAGS) $(ROOTLIBS) SampleHandler.o DrawMC.o -o DrawMC.exe

fitMgg:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

sPlot:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) $(ROOSTATSFLAGS) -o sPlot.exe $(ROOTFLAGS) sPlot.cc

clean:
	rm *.o
	rm DrawMC.exe fitMgg.exe sPlot.exe
	rm -r DrawMC.exe.dSYM fitMgg.exe.dSYM sPlot.exe.dSYM
