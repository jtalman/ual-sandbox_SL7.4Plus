CC       = gcc
#CCFLAGS  = -g -fpic -ansi -DsxfCheck -Wall -Wextra -fpermissive
CCFLAGS  = -O0 -g3

#INC  += -I. -I./src

compile: ./1TurnFromOriginTwissFnctns_X ./trnsfrMtrx_X

clean:
	@rm -f 1TurnFromOriginTwissFnctns_X 1TurnFromOriginTwissFnctns_X.o trnsfrMtrx_X trnsfrMtrx_X.o

./1TurnFromOriginTwissFnctns_X: ./1TurnFromOriginTwissFnctns_X.o
	@$(CC) -o $@  $(CCFLAGS) ./1TurnFromOriginTwissFnctns_X.o -lm
	@echo "..."
	@echo "      post processing one turn from origin Twiss Functions X"
	@echo "..."
	@./1TurnFromOriginTwissFnctns_X

./1TurnFromOriginTwissFnctns_X.o:
	@$(CC) $(CCFLAGS) $(INC) -c ./1TurnFromOriginTwissFnctns_X.c -o $@

./trnsfrMtrx_X: ./trnsfrMtrx_X.o
	@$(CC) -o $@  $(CCFLAGS) ./trnsfrMtrx_X.o -lm
#	@echo "..."
#	@echo "      post processing trnsfrMtrx_X"
#	@echo "..."
#	                                         <<<--- this file is ca most likely to be misspecified for SP
#	@./trnsfrMtrx_X ../propagate/out/StndrdPrtcl4 161
#	                                         <<<--- this file is ca most likely to be misspecified for SP

./trnsfrMtrx_X.o:
	@$(CC) $(CCFLAGS) $(INC) -c ./trnsfrMtrx_X.c -o $@
