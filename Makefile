#Used compiler
CC = g++

# APP name
APP_NAME := raytracer

# Directories
SRC_DIR := ./src
OBJ_DIR := ./objects
INCLUDE_DIR := ./include

# Source files
CPP_SRC = $(wildcard $(SRC_DIR)/*.cpp)
H_SRC = $(wildcard $(SRC_DIR)/*.h)

# Object files
OBJS_FILES = $(subst .cpp,.o,$(subst src,objects,$(CPP_SRC)))

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude 

#Aditional compile options
COMPILER_FLAGS = -O2 

#Executable name
EXE_NAME = bin/$(APP_NAME).exe

all : main

main: $(OBJS_FILES)
	$(CC) $(OBJS_FILES) main.cpp $(INCLUDE_PATHS) $(COMPILER_FLAGS) -o $(EXE_NAME)

$(OBJ_DIR)/%.o: ./src/%.cpp
	$(CC) -c $(INCLUDE_PATHS) $< -o $@

%.o: %.c
	$(CC) -c $(INCLUDE_PATHS) $< -o $@

clean:
	del $(subst /,\\,$(OBJ_DIR))\*.o
cleanIm:
	del $(subst /,\\,./images)\*.ppm

