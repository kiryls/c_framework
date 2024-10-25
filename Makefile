EXEC := app

BUILD_DIR := ./build
SRC_DIR := ./src
BIN_DIR := $(BUILD_DIR)/src
CONFIG_DIR := ./config

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

# CFLAGS := -Wvla -Wextra -Werror -pthread
CFLAGS :=
CPPFLAGS := $(INC_FLAGS) -MMD -MP
LDFLAGS :=

$(BUILD_DIR)/$(EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "building '$@':"
	$(CC) $(OBJS) -o $@
	@echo ""

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo "compiling '$@':"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo ""

all: $(OBJS)

run: $(BUILD_DIR)/$(EXEC)
	@echo "output:"
	@$(BUILD_DIR)/$(EXEC)

.PHONY: git clean

f := .
git:
	git add $f
	git commit -m "$(msg)"
	git push origin main

clean:
	rm -r $(BUILD_DIR)
