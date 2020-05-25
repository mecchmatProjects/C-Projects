# source, object and header files
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=obj/%.o)
HEADER := $(wildcard headers/*.h)

# preprocessor flags
CPPFLAGS := -Iheaders

# compiler flags
CXXFLAGS := -Wall -std=c++17

all : main

main : $(OBJ) obj/main.o
	$(CXX) -o $@ $^ $(LDLIBS)

obj/main.o : tests/main.cpp $(HEADERS) | obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

obj/%.o : src/%.cpp $(HEADER) | obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

obj :
	mkdir $@

clean : 
	$(RM) -r obj main

.PHONY : clean all

