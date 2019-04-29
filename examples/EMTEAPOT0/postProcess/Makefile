CC       = gcc
#CCFLAGS  = -g -fpic -ansi -DsxfCheck -Wall -Wextra -fpermissive
CCFLAGS  = -O0 -g3

#INC  += -I. -I./src

compile: ./betas

clean:
	@rm -f betas betas.o
#	rm -f betas betas.o getSP.o

#./betas: ./betas.o ./getSP.o
./betas: ./betas.o
	@$(CC) -o $@  $(CCFLAGS) ./betas.o
#	$(CC) -o $@  $(CCFLAGS) $(INC) ./betas.o
	@echo "..."
	@echo "      post processing"
	@echo "..."
#	                                         <<<--- this file is ca most likely to be misspecified for SP
	@./betas ../propagate/out/StndrdPrtcl4
#	                                         <<<--- this file is ca most likely to be misspecified for SP
#	@./run_betas

./betas.o:
	@$(CC) $(CCFLAGS) $(INC) -c ./betas.c -o $@
