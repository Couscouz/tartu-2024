PROGRAM = launcher

# The needed object files (we make these from the source code)
OBJ = main.o functions.o
CFLAGS = -Wall
 
# This is the first target. It will be built when you run 'make' or 'make all'
all: $(PROGRAM)
 
# Rule for linking IMPORTANT! The space in front of $(CXX) is a TABULATOR!
$(PROGRAM): $(OBJ)
		$(CXX) $(OBJ) -o $(PROGRAM)
 
# Rules for compiling
main.o: main.cpp
		$(CXX) -c main.cpp -o main.o $(CFLAGS)
 
functions.o: functions.cpp
		$(CXX) -c functions.cpp -o functions.o $(CFLAGS)