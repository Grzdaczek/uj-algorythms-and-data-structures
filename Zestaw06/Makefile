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

HPP			+= BinaryTree.hpp
#=-----------------------------------------------------------------------------

all: BinaryTree.x

run: all
	$(Q)./BinaryTree.x

%.x: %.o
	@printf "  LD\t$^\n"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PRECIOUS: %.o
%.o: %.cpp $(HPP)
	@printf "  CXX\t$<\n"
	$(Q)$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) *.o *.x *.a *.so

.PHONY: all clean
