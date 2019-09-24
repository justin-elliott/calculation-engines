# Makefile

CXX			:= gcc
CXXFLAGS	:= -std=c++17 -pedantic-errors -Wall -Wextra -Werror
INCLUDE		:= -Iinclude/
LDFLAGS		:= -L/usr/lib -lstdc++ -lm
BUILD		:= ./build
OBJ_DIR		:= $(BUILD)/obj
TARGET_DIR	:= $(BUILD)
TARGET		:= calc

SRC 		:= $(wildcard src/*.cpp)
OBJ			:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(TARGET_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJ)

.PHONY: all

all: build $(TARGET_DIR)/$(TARGET)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -vf $(TARGET_DIR)/$(TARGET)