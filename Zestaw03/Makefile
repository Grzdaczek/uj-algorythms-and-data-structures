Q		:= @
CXX		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CXXFLAGS	+= -Wall
CXXFLAGS	+= -O2
CXXFLAGS	+= -pedantic
CXXFLAGS	+= -std=c++17

HPP		+= LinkedList.hpp
#=-----------------------------------------------------------------------------

all: List.x

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
