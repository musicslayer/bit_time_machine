# Tools
SHELL := bash

# Compiler
CXX = g++
FLAGS = -I include -std=c++20 -mconsole -Wall -Wextra -Werror -Wpedantic -MMD -MP

CXXFLAGS_RELEASE = $(FLAGS) -O2
CXXFLAGS_DEBUG = $(FLAGS) -g -O0

# App Information
APP_NAME_RELEASE = myapp
APP_NAME_DEBUG = myapp_debug

# Source
SRC_DIR = src
SRCS := $(shell shopt -s globstar nullglob; echo $(SRC_DIR)/**/*.cpp)

# Output
OUTPUT_DIR = output
BUILD_DIR = $(OUTPUT_DIR)/build
BIN_DIR = $(OUTPUT_DIR)/bin

BUILD_DIR_RELEASE = $(BUILD_DIR)/release
BUILD_DIR_DEBUG = $(BUILD_DIR)/debug
BIN_DIR_RELEASE = $(BIN_DIR)/release
BIN_DIR_DEBUG = $(BIN_DIR)/debug

OBJS_RELEASE = $(subst $(SRC_DIR)/, $(BUILD_DIR_RELEASE)/, $(SRCS:.cpp=.o))
OBJS_DEBUG = $(subst $(SRC_DIR)/, $(BUILD_DIR_DEBUG)/, $(SRCS:.cpp=.o))

DEPS_RELEASE = $(OBJS_RELEASE:.o=.d)
DEPS_DEBUG = $(OBJS_DEBUG:.o=.d)
-include $(DEPS_RELEASE) $(DEPS_DEBUG)

# Verbosity
AT = $(if $(VERBOSE),,@)

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

.PHONY: release
release: $(BIN_DIR_RELEASE)/$(APP_NAME_RELEASE)

.PHONY: debug
debug: $(BIN_DIR_DEBUG)/$(APP_NAME_DEBUG)

.PHONY: run
run: release
	@$(BIN_DIR_RELEASE)/$(APP_NAME_RELEASE)

.PHONY: run-debug
run-debug: debug
	@gdb --args $(BIN_DIR_DEBUG)/$(APP_NAME_DEBUG)

.PHONY: clean
clean:
	@rm -rf "$(OUTPUT_DIR)"

.PHONY: rebuild
rebuild: clean all

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all       - Build everything"
	@echo "  make release   - Build the release version"
	@echo "  make debug     - Build the debug version"
	@echo "  make run       - Build and run the release version"
	@echo "  make run-debug - Build and run the debug version in gdb"
	@echo "  make clean     - Remove all build artifacts"
	@echo "  make rebuild   - Clean and rebuild everything"
	@echo "  make help      - View all available targets"