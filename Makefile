SRCPATH:=./src
EXEC_FILE := pdpa1

CC = g++ 
CFLAGS = -g -Wall -lX11

#CDEFINE:= -DRSEED 
CDEFINE:= -DRZ

dummy:sa

.PHONY : all clean


all : $(EXEC_FILE) 

nr: CDEFINE := -DTEST_NRESTORE

sa: CDEFINE := -DSIMU_ANNEAL

pa: CDEFINE := -DTEST_PARSER


nr sa pa:clean all


rmmain:
	@rm $(SRCPATH)/main.o


$(EXEC_FILE): ./src/$(EXEC_FILE)
	@mv $< .

./src/$(EXEC_FILE):
	@echo "> compiling src: "
	@cd $(SRCPATH); make CDEFINE=$(CDEFINE)
	
clean : 
	@echo "> clean src: "
	@cd $(SRCPATH); make clean
	@rm -f $(EXEC_FILE)
