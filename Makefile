SRCPATH:=./src
EXEC_FILE := pdpa1

CFLAGSO := -g -Wall
#CDEFINE:= -DRSEED 
CDEFINE:= -DRZ

.PHONY : all clean


all : $(EXEC_FILE) 

#nr: CDEFINE := -DTEST_NRESTORE

#sa: CDEFINE := -DSIMU_ANNEAL

#pa: CDEFINE := -DTEST_PARSER

gui: CDEFINE := -DGUI

gui: CGUIO := -lX11

gui: EXEC_FILE := pdpa1_gui
#gui: CFLAGSO = -g -Wall -lX11


#nr sa pa :clean all

gui: cleangui all

rmmain:
	@rm $(SRCPATH)/main.o


$(EXEC_FILE): ./src/$(EXEC_FILE)
	@echo "> build: $(EXEC_FILE) "
	@mv ./src/$(EXEC_FILE) .

./src/$(EXEC_FILE):
	@echo "> compiling src: "
	@cd $(SRCPATH); make CDEFINE=$(CDEFINE) CFLAGSO=$(CFLAGSO) CGUIO=$(CGUIO) EXEC_FILE0=$(EXEC_FILE)
	
clean : 
	@echo "> clean src: "
	@cd $(SRCPATH); make clean
	@rm -f $(EXEC_FILE)

cleangui : 
	@echo "> clean src: "
	@cd $(SRCPATH); make clean
