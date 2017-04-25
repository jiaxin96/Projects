CC := g++-4.8
FLAGE := -std=c++11 -Wall -g
INCLUDE_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin/
ALL_FILE :=$(BUILD_DIR)/Agenda.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o  $(BUILD_DIR)/Storage.o $(BUILD_DIR)/User.o
INCLUDE := -I ./$(INCLUDE_DIR)
$(BIN_DIR)/Agenda:$(ALL_FILE)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(FLAGE) $(INCLUDE) $^ -o $@
$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(FLAGE) $(INCLUDE) -c $^ -o $@
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
