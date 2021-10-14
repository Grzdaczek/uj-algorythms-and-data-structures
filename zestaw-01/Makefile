Q		:= @
CC		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CCFLAGS		+= -Wall
CCFLAGS		+= -O2
CCFLAGS		+= -pedantic
#=-----------------------------------------------------------------------------

all: Stack.x Generator.x

Stack.x: Stack.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

Generator.x: Generator.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	@printf "  CC\t$<\n"
	$(Q)$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean