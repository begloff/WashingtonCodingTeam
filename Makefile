# Author: Benjamin Egloff
# E-mail: begloff@nd.edu
#
# This is the Makefile for Final Project

# g++ is for the GCC compiler for C++
CC := g++

# CFLAGS are the compiler flages for when we compile C code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)


# Run Compilation Command
# Command: make PC07

$(OBJ)/roadtrip.o: $(SRC)/roadtrip.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/roadtrip.cpp -o $@
	
$(OBJ)/final_proj.o: $(SRC)/final_proj.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/final_proj.cpp -o $@

FinalObjs :=  $(OBJ)/final_proj.o $(OBJ)/roadtrip.o

Final: $(initialize) $(FinalObjs)
	$(CC) $(CXXFLAGS) -o $(EXE)/Final $(FinalObjs)
	

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*