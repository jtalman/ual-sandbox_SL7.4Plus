include ./Makefile.config

# JDT2018 DIRS = ./src ./examples ./api # ./doc
DIRS = ./src

compile:  
	@for dir in $(DIRS); do \
	(cd $$dir; if [ -f ./Makefile ]; then $(MAKE) compile; fi;); \
	done

clean: 
	@for dir in $(DIRS) ; do \
	(cd $$dir; if [ -f ./Makefile ]; then $(MAKE) clean; fi;); \
	done
