Q		:= @
CXX		:= g++
LD		:= g++
AR		:= ar rv
RM		:= rm -rf

CXXFLAGS	+= -Wall
CXXFLAGS	+= -O2
CXXFLAGS	+= -g
CXXFLAGS	+= -pedantic
CXXFLAGS	+= -std=c++17

HPP		+= ArrayList.hpp
HPP		+= CursorList.hpp
HPP		+= iterator.hpp
#=-----------------------------------------------------------------------------

all: ArrayList.x CursorList.x # Generator.x

run: all
	./CursorList.x

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
