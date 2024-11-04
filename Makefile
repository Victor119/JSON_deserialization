EXECUTABLE_NAME = json_eval
BUILD_DIR = build

build:
	@mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	@cp $(BUILD_DIR)/$(EXECUTABLE_NAME) $(EXECUTABLE_NAME)

tests: build
	@cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXECUTABLE_NAME)

.PHONY: build tests clean
