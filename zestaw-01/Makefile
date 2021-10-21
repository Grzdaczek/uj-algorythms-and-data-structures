Q		:= @
CC		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CCFLAGS	+= -Wall
CCFLAGS	+= -O2
CCFLAGS	+= -pedantic

HPP		+= LinkedStack.hpp
HPP		+= ArrayStack.hpp
#=-----------------------------------------------------------------------------

all: Stack.x Generator.x ONP.x

Stack.x: Stack.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

ONP.x: ONP.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

Generator.x: Generator.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp $(HPP)
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
