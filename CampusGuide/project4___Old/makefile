CC := g++
FLAGS := -std=c++11 -w -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)
$(BIN_DIR)/test: $(BUILD_DIR)/main.o  $(BUILD_DIR)/Guide_service.o $(BUILD_DIR)/Guide_UI.o $(BUILD_DIR)/Graph.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/Spot.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $^

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/main.cpp

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
	@rm $(INC_DIR)/*.gch
