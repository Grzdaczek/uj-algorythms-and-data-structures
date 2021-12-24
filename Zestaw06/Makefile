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

test: all
	$(Q)./BinaryTree.x < tests/input/100.txt > tests/result/100.txt
	$(Q)./BinaryTree.x < tests/input/10k.txt > tests/result/10k.txt
	$(Q)./BinaryTree.x < tests/input/15a.txt > tests/result/15a.txt
	$(Q)./BinaryTree.x < tests/input/15b.txt > tests/result/15b.txt
	$(Q)diff -rq tests/expected tests/result

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
