# Compiler and build flags
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
INCLUDES := -Iinclude
SRC_DIR  := src
OBJ_DIR  := obj
TARGET   := similarity_detector

# Automatically collect all .cpp source files and map them to .o object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default build target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile each .cpp file into an object file inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Quick run using provided test files
run: $(TARGET)
	./$(TARGET) tests/sample1.txt tests/sample2.txt

# Clean compiled objects and binary
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all run clean
