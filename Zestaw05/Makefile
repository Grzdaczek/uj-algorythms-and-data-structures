Q		:= @
CXX		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CXXFLAGS	+= -Wall
CXXFLAGS	+= -O3
CXXFLAGS	+= -g
CXXFLAGS	+= -pedantic
CXXFLAGS	+= -std=c++17
CXXFLAGS	+= -march=native

#=-----------------------------------------------------------------------------

all: BubbleSort.x InsertionSort.x SelectionSort.x

test: all
	$(Q)./BubbleSort.x < in.dat > out.dat
	$(Q)diff exp.dat out.dat --color -q

%.x: %.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp $(HPP)
	@printf "  CXX\t$<\n"
	$(Q)$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
