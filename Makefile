# Directories
SRC_DIR := src
OBJ_DIR := $(SRC_DIR)/obj
HPP_DIR := $(SRC_DIR)/hppDir
CPP_DIR := $(SRC_DIR)/cppDir
DOC_DIR := doc

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -pedantic

# Source files and object files
SOURCES := $(wildcard $(CPP_DIR)/*.cpp) $(SRC_DIR)/main.cpp
OBJECTS := $(patsubst $(CPP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
HEADERS := $(wildcard $(HPP_DIR)/*.h)

# Executable file
EXECUTABLE := palagdan


# Linking object files to generate the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creating the object directory
$(OBJ_DIR):
	mkdir -p $@

# Generate Doxygen documentation
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

# Default target
all: compile doc tests

# Compile the project
compile: $(EXECUTABLE)

# Run the project
run: compile
	@./$(EXECUTABLE) examples/correct/config1.ini

# Clean object files, executables, and generated documentation
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE) $(DOC_DIR)/* $(TEST_OBJ_DIR) $(TEST_EXECUTABLE)

.PHONY: all doc compile run clean clean_server_files

# Clean server files
clean_server_files:
	rm -rf server_db server.log


# TESTS
# Test files and object files
TESTS_DIR = $(SRC_DIR)/tests
TEST_SOURCES := $(wildcard $(TESTS_DIR)/*.cpp)
TEST_HEADERS := $(wildcard $(TESTS_DIR)/*.h)
TEST_OBJ_DIR := $(SRC_DIR)/test_obj
TEST_OBJECTS := $(patsubst $(TESTS_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SOURCES))
TEST_EXECUTABLE := test_runner

# # Generating test executable
$(TEST_EXECUTABLE): $(TEST_OBJECTS) src/obj/utils.o src/obj/request.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# # Compiling test files into object files
$(TEST_OBJ_DIR)/%.o: $(TESTS_DIR)/%.cpp $(HEADERS) $(TEST_HEADERS) | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJ_DIR):
	mkdir -p $@

tests: tests_compile
tests_compile: $(TEST_EXECUTABLE)
run_tests:
	@./$(TEST_EXECUTABLE)
.PHONY: compile_tests
