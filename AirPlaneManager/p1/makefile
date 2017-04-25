
CC := clang++
FLAGS := -std=c++11 -Wall -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)
$(BIN_DIR)/main: $(BUILD_DIR)/main.o  $(BUILD_DIR)/Plane.o $(BUILD_DIR)/queue.o $(BUILD_DIR)/Extended_queue.o $(BUILD_DIR)/Random.o $(BUILD_DIR)/Runway.o
	@mkdir -p $(BIN_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $^

# $(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/main.cpp

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
