#Used compiler
CC = g++

# APP name
APP_NAME := raytracer

# Directories
SRC_DIR := ./src
INCLUDE_DIR := ./include

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS_FILES = $(subst .cpp,.o,$(subst source,objects,$(SRC_FILES)))

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Aditional compile options
COMPILER_FLAGS = -O2 

#Executable name
EXE_NAME = bin/$(APP_NAME).exe

all : main

main: $(OBJS_FILES)
	$(CC) $(OBJS_FILES) main.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -o $(EXE_NAME)

%.o: %.cpp
	$(CC) -c $(INCLUDE_PATHS) $< -o $@

%.o: %.c
	$(CC) -c $(INCLUDE_PATHS) $< -o $@

clean:
	del $(subst /,\\,$(SRC_DIR))\*.o

