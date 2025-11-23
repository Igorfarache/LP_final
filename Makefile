# Makefile for C++ project
# Version corrigida com caminhos 8.3 compatíveis com Windows

INCLUDE_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Final executable
TARGET := $(BIN_DIR)/app.exe

# Default rule
all: setup $(TARGET)

# Create build and bin directories
setup:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run:
	./bin/app.exe

# Clean build artifacts
clean:
	rmdir /s /q $(BUILD_DIR) 2>nul || true
	rmdir /s /q $(BIN_DIR) 2>nul || true

# Rebuild everything
rebuild: clean all