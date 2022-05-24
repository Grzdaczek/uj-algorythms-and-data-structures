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

HPP			+= Dict.hpp

#=-----------------------------------------------------------------------------

all: Dict.x

test: all
	$(Q)./Dict.x tests/input/10_arg.txt < tests/input/10_std.txt > tests/result/10.txt
	$(Q)./Dict.x tests/input/65k_arg.txt < tests/input/65k_std.txt > tests/result/65k.txt
	$(Q)diff -rq tests/expected tests/result
	@printf "  TEST\tall tests passed\n"

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
