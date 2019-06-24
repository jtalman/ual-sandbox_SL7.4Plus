CC       = g++                       # Compiler
CCFLAGS  = -g -fpic -ansi -DsxfCheck -Wall -Wextra -fpermissive     # Compilation flags

INC  += -I. -I./src
INC  += -I$(UAL)/ext/UI/include
INC  += -I$(UAL_SXF)/src
INC  += -I$(UAL_ACCSIM)/src
INC  += -I$(UAL_TEAPOT)/src
INC  += -I$(UAL_ETEAPOT)/src
INC  += -I$(UAL_ETEAPOT_MltTurn)/src
INC  += -I$(UAL_EMTEAPOT)/src
INC  += -I$(UAL_PAC)/src
INC  += -I$(UAL)/codes/UAL/include
INC  += -I$(UAL_ZLIB)/src
INC  += -I$(UAL)/tools/include
INC  += -I$(SXFV)/src
INC  += -I/home/ual/tools/gsl/include

LIBS += -L$(UAL)/tools/lib/linux                 -lgsl
LIBS += -L$(UAL)/ext/UI/lib/$(UAL_ARCH)  	 -lUalUI
LIBS += -L$(UAL_TIBETAN)/lib/$(UAL_ARCH)  	 -lTibetan
LIBS += -L$(UAL_SXF)/lib/$(UAL_ARCH) 		 -lUalSXF2
LIBS += -L$(UAL_ACCSIM)/lib/$(UAL_ARCH) 	 -lAccsim
LIBS += -L$(UAL_TEAPOT)/lib/$(UAL_ARCH) 	 -lTeapot
LIBS += -L$(UAL_ETEAPOT)/lib/$(UAL_ARCH) 	 -lETeapot
LIBS += -L$(UAL_ETEAPOT_MltTurn)/lib/$(UAL_ARCH) -lETEAPOT_MltTurn
LIBS += -L$(UAL_EMTEAPOT)/lib/$(UAL_ARCH)        -lEMTEAPOT
LIBS += -L$(UAL_PAC)/lib/$(UAL_ARCH)  		 -lPacSMF -lPacOptics -lPac
LIBS += -L$(UAL_ZLIB)/lib/$(UAL_ARCH) 		 -lZTps
LIBS += -L$(UAL)/codes/UAL/lib/$(UAL_ARCH) 	 -lUal
LIBS += -L$(SXFV)/lib/$(UAL_ARCH) 		 -lSXF
LIBS += -L$(UAL)/tools/lib/$(UAL_ARCH) 		 -lpcre -lxml2 -lrfftw -lfftw
LIBS += 					 -lm

compile: ./postSxfPropagator

clean:
	@rm -f postSxfPropagator postSxfPropagator.cc postSxfPropagator.o
	@rm -rf out/*

./postSxfPropagator: ./postSxfPropagator.o
	$(CC) -o $@  $(CCFLAGS) $(INC) ./postSxfPropagator.o $(LIBS)
	@echo "..."
	@echo "      propagating post sxf"
	@echo "..."
	./run_standardBunch

./postSxfPropagator.o:
	$(CC) $(CCFLAGS) $(INC) -c ./postSxfPropagator.cc -o $@
