SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))
EXE := $(EXEC_FILE0)
CXX := g++
#CFLAGS = -g -Wall  $(CDEFINE)
CFLAGS := $(CFLAGSO) $(CDEFINE) $(CGUIO)

.PHONY : depend all clean


all: $(EXE)

$(EXE) : $(OBJS)
	@echo "> compiling: $<"
	@$(CXX) $(CFLAGS) $(OBJS) -o $(EXE)

%.o : %.cpp
	@echo "> compiling: $<"
	@$(CXX) $(CFLAGS) -c -o $@ $<

%.d: %.cpp
	@$(CXX) -MM -MG "$<" | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@
	

DEP := $(OBJS:.o=.d)

-include $(DEP)


depend: $(DEP)
clean:
	@rm -f *.o *.d $(EXE)


