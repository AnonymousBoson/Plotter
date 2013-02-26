CC				= g++
CCFLAGS		=	-Wall -g
SOURCES 	= 
ROOTFLAGS	= `root-config --cflags --glibs`
ROOFITFLAGS = -lRooFit -lRooFitCore
ROOSTATSFLAGS = -lRooStats 

all:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) $(ROOSTATSFLAGS) -o sPlot.exe $(ROOTFLAGS) sPlot.cc

DrawMC:
	$(CC) $(CCFLAGS) -o DrawMC.exe $(ROOTFLAGS) DrawMC.cc

fitMgg:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) -o fitMgg.exe $(ROOTFLAGS) fitMgg.cc

sPlot:
	$(CC) $(CCFLAGS) $(ROOFITFLAGS) $(ROOSTATSFLAGS) -o sPlot.exe $(ROOTFLAGS) sPlot.cc

clean:
	rm DrawMC.exe fitMgg.exe sPlot.exe
	rm -r DrawMC.exe.dSYM fitMgg.exe.dSYM sPlot.exe.dSYM
