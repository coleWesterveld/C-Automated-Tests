CC = gcc
CFLAGS = -Wall -std=c99 -g -pedantic -DUNITY_OUTPUT_COLOR

# TODO: CHANGE FILE NAME HERE
SRC_NAME = lastnameFirstnameA1
MAIN_NAME = $(SRC_NAME)Main
# will automatically compile the project with DATA_FILE as a command line argument
DATA_FILE = a1Data.txt

# Directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/Debug
PRIVATE_DIR = private
TEST_DIR = tests

# Targets
TEST_TARGET = $(BUILD_DIR)/test_$(SRC_NAME)
MAIN_TARGET = $(BUILD_DIR)/$(SRC_NAME)

# Object files
TEST_OBJS = $(BUILD_DIR)/test_assignment.o $(BUILD_DIR)/unity.o 
ASSIGNMENT_OBJS = $(BUILD_DIR)/$(SRC_NAME).o
MAIN_OBJS = $(BUILD_DIR)/$(SRC_NAME).o $(BUILD_DIR)/$(MAIN_NAME).o

# Default target (build main program)
all: $(MAIN_TARGET)

# Compile assignment files
$(BUILD_DIR)/$(SRC_NAME).o: $(PRIVATE_DIR)/$(SRC_NAME).c $(PRIVATE_DIR)/givenA1.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(MAIN_NAME).o: $(PRIVATE_DIR)/$(MAIN_NAME).c $(PRIVATE_DIR)/givenA1.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files (now in tests/ directory)
$(BUILD_DIR)/test_assignment.o: $(TEST_DIR)/test_assignment.c $(PRIVATE_DIR)/givenA1.h $(TEST_DIR)/unity.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/unity.o: $(TEST_DIR)/unity.c $(TEST_DIR)/unity.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run tests
test: $(TEST_TARGET)
	@echo "\n"
	@echo "\033[1;34m==================== RUNNING TESTS ====================\033[0m"
	@./$(TEST_TARGET)
	@echo "\033[1;34m==================== END OF TESTS ====================\033[0m"
	@echo "\n"

$(TEST_TARGET): $(TEST_OBJS) $(ASSIGNMENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run the main program
main: $(MAIN_TARGET) $(PRIVATE_DIR)/$(DATA_FILE)
	@echo "\n"
	@echo "\033[1;32m==================== RUNNING MAIN PROGRAM ====================\033[0m"
	@./$(MAIN_TARGET) $(PRIVATE_DIR)/$(DATA_FILE)
	@echo "\033[1;32m==================== END OF MAIN PROGRAM =====================\033[0m"
	@echo "\n"

$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

debug: $(DEBUG_DIR)/$(SRC_NAME) $(PRIVATE_DIR)/$(DATA_FILE)

# Debug executable target for main program
$(DEBUG_DIR)/$(SRC_NAME): $(MAIN_OBJS)
	mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build files
clean:
	find $(BUILD_DIR) -type f \( -name '*.o' -o -name '*.out' -o -name '*.exe' -o -name '*.a' -o -name '*.so' -o -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' \) -delete
	rm -f $(TEST_TARGET) $(MAIN_TARGET)
