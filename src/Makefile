SRCPATH:=./
EXEC_FILE := pdpa1
#得到所有.cpp文件的名称，去除路径  
SRC:=$(wildcard $(SRCPATH)*.cpp)  
#SRC:=$(notdir $(SRC))  
  
  
CC = g++ 
  
CFLAGS = -g -Wall  
  
# makefile 的程序入口！  
all : main 
	@echo "enter regular: all..."  
main : $(SRC)  
	$(CC) $(CFLAGS) -o $(EXEC_FILE) $(SRC)
 
clean:  
	@echo "i will clean..."  
	-rm -rf *.o *.d $(EXEC_FILE)
	@echo "ok,i have cleaned!"  
	  
print:  
	echo $(SRC) 

