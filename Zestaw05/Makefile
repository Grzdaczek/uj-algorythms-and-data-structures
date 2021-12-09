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

all: BubbleSort.x InsertionSort.x SelectionSort.x SelectionSortComplexity.x Generator.x 

test: all
	$(Q)python3 test.py

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
