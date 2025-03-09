# Compiler and flags
CXX=g++# The C++ compiler
CXXFLAGS=-g -Wall -std=c++17  # Compiler flags (enable all warnings and use C++17 standard)

# Directories
SRC_DIR=src
INC_DIR=include
BUILD_DIR=build
TARGET=wfc
# Source and object files
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Default rule to build the project
all: clean $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) -I $(INC_DIR) # Link object files to create the executable

# Rule to compile .cpp files into .o object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@  # Compile each source file

# Clean rule to remove build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)  # Remove build directory and executable

# Rule to run the program after building
run: $(TARGET)
	./$(TARGET) $(ARGS)  # Run the program with optional arguments

# Phony targets to avoid conflicts with file names
.PHONY: all clean
