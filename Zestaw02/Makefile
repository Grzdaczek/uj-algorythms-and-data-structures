Q		:= @
CC		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CCFLAGS	+= -Wall
CCFLAGS	+= -O2
CCFLAGS	+= -pedantic
CCFLAGS	+= -std=c++17

HPP		+= LinkedQueue.hpp
HPP		+= ArrayQueue.hpp
#=-----------------------------------------------------------------------------

all: Queue.x Generator.x

Queue.x: Queue.o
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
