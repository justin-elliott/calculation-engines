# Makefile

CXX				:= g++
CXXFLAGS		:= -std=c++17 -pedantic-errors -Wall -Wextra -Werror
INCLUDE			:= -I. -Ithird_party/
LDFLAGS			:= -L/usr/lib -lstdc++ -lm
BUILD			:= ./build
OBJ_DIR			:= $(BUILD)/obj
TARGET_DIR		:= $(BUILD)
TARGET			:= calc
TEST_TARGET		:= calc_test

SRC 			:= $(wildcard src/*.cpp)
OBJ				:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TEST_SRC 		:= $(wildcard src/*.cpp test/*.cpp)
TEST_OBJ		:= $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ		:= $(filter-out $(OBJ_DIR)/src/main.o, $(TEST_OBJ))

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_TEST_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(TARGET_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJ)

$(TARGET_DIR)/$(TEST_TARGET): $(TEST_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(TARGET_DIR)/$(TEST_TARGET) $(TEST_OBJ)

.PHONY: all

all: build $(TARGET_DIR)/$(TARGET)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -vf $(TARGET_DIR)/$(TARGET)

test: build $(TARGET_DIR)/$(TEST_TARGET)
	$(TARGET_DIR)/$(TEST_TARGET)
