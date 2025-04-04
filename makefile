# Command Line Options
AT = $(if $(VERBOSE),,@)

# Tools
CLANG_FORMAT := clang-format
CLANG_TIDY := clang-tidy
SHELL := bash

# App Information
APP_NAME_RELEASE := myapp
APP_NAME_DEBUG := myapp_debug

# Source
SRC_DIR := src
SRCS := $(shell bash -c 'shopt -s globstar nullglob; echo $(SRC_DIR)/**/*.cpp')
HDR_DIR := include
HDRS := $(shell bash -c 'shopt -s globstar nullglob; echo $(HDR_DIR)/**/*.h')

# Compiler
CXX := g++

CXXFLAGS := -I $(HDR_DIR) -std=c++20 -Wall -Wextra -Werror -Wpedantic -MMD -MP
CXXFLAGS_LINT := $(CXXFLAGS) -Wno-unknown-warning-option
CXXFLAGS_RELEASE := $(CXXFLAGS) -mconsole -O2
CXXFLAGS_DEBUG := $(CXXFLAGS) -mconsole -g -O0

# Output
OUTPUT_DIR := output
BUILD_DIR := $(OUTPUT_DIR)/build
BIN_DIR := $(OUTPUT_DIR)/bin

BUILD_DIR_RELEASE := $(BUILD_DIR)/release
BUILD_DIR_DEBUG := $(BUILD_DIR)/debug
BIN_DIR_RELEASE := $(BIN_DIR)/release
BIN_DIR_DEBUG := $(BIN_DIR)/debug

OBJS_RELEASE := $(subst $(SRC_DIR)/, $(BUILD_DIR_RELEASE)/, $(SRCS:.cpp=.o))
OBJS_DEBUG := $(subst $(SRC_DIR)/, $(BUILD_DIR_DEBUG)/, $(SRCS:.cpp=.o))

DEPS_RELEASE := $(OBJS_RELEASE:.o=.d)
DEPS_DEBUG := $(OBJS_DEBUG:.o=.d)
-include $(DEPS_RELEASE) $(DEPS_DEBUG)

# Build Rules
$(BUILD_DIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(AT)$(CXX) $(CXXFLAGS_RELEASE) -c $< -o $@

$(BUILD_DIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(AT)$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(BIN_DIR_RELEASE)/$(APP_NAME_RELEASE): $(OBJS_RELEASE)
	@mkdir -p $(dir $@)
	$(AT)$(CXX) $(CXXFLAGS_RELEASE) $^ -o $@

$(BIN_DIR_DEBUG)/$(APP_NAME_DEBUG): $(OBJS_DEBUG)
	@mkdir -p $(dir $@)
	$(AT)$(CXX) $(CXXFLAGS_DEBUG) $^ -o $@

# Targets
.DEFAULT_GOAL := all

.PHONY: all
all: release debug

.PHONY: clean
clean:
	@rm -rf "$(OUTPUT_DIR)"

.PHONY: debug
debug: $(BIN_DIR_DEBUG)/$(APP_NAME_DEBUG)

.PHONY: format
format:
	@echo "Formatting source files..."
	@$(CLANG_FORMAT) -i $(SRCS) $(HDRS)

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all       - Build everything"
	@echo "  make clean     - Remove all build artifacts"
	@echo "  make debug     - Build the debug version"
	@echo "  make format    - Run the formatter (uses .clang-format)"
	@echo "  make help      - View all available targets"
	@echo "  make lint      - Run the linter (uses .clang-tidy)"
	@echo "  make rebuild   - Clean and rebuild everything"
	@echo "  make release   - Build the release version"
	@echo "  make run       - Build and run the release version"
	@echo "  make run-debug - Build and run the debug version in gdb"

.PHONY: lint
lint:
	@echo "Linting source files..."
	@$(CLANG_TIDY) --quiet $(SRCS) $(HDRS) -- -x c++ $(CXXFLAGS_LINT)

.PHONY: rebuild
rebuild: clean all

.PHONY: release
release: $(BIN_DIR_RELEASE)/$(APP_NAME_RELEASE)

.PHONY: run
run: release
	@$(BIN_DIR_RELEASE)/$(APP_NAME_RELEASE)

.PHONY: run-debug
run-debug: debug
	@gdb --args $(BIN_DIR_DEBUG)/$(APP_NAME_DEBUG)