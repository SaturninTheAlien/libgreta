# Pekka Kana 2 by Janne Kivilahti from Piste Gamez (2003-2007)
# https://pistegamez.net/game_pk2.html
# 
# This is a library to handle PK2 assets
#

# Compiler:
CXX = c++


# Warnings:
CXXFLAGS += -Wall

# Standart:
CXXFLAGS += --std=c++17 -fPIC

# Compiling to dll
LDFLAGS += -shared 

ifdef DEBUG
$(info ->Debugging symbols enabled) 
    CXXFLAGS += -g
	LDFLAGS += $(shell pkg-config lua --libs)
	BIN_DIR = bin/
else
$(info ->Release mode)
    CXXFLAGS += -O3
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS += -undefined dynamic_lookup
	endif
endif


CXXFLAGS += $(shell pkg-config lua --cflags)


COMPILE_COMMAND = $(CXX) $(CXXFLAGS)

# Directories:
SRC_DIR = src/

BUILD_DIR = build/

# Source files:
SRC  = *.cpp */*.cpp */*/*.cpp
SRC := $(addprefix $(SRC_DIR), $(SRC))
SRC := $(wildcard $(SRC))

# Object files:
OBJ := $(basename $(SRC))
OBJ := $(subst $(SRC_DIR), ,$(OBJ))
OBJ := $(addsuffix .o, $(OBJ))
OBJ := $(addprefix $(BUILD_DIR), $(OBJ))

# Dependency files:
DEPENDENCIES := $(OBJ)
DEPENDENCIES := $(basename $(DEPENDENCIES))
DEPENDENCIES := $(addsuffix .d, $(DEPENDENCIES))

# Binary output:
BIN = $(BIN_DIR)greta.so

all: $(BIN)

###########################
$(BIN): $(OBJ)
	@echo -Linking libgreta
	@mkdir -p $(dir $@) >/dev/null
	@$(CXX) $^ $(LDFLAGS) -o $@

###########################
-include $(DEPENDENCIES)

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@echo -Compiling $<
	@mkdir -p $(dir $@) >/dev/null
	@$(COMPILE_COMMAND) -I$(SRC_DIR) -o $@ -c $<
	@$(COMPILE_COMMAND) -MM -MT $@ -I$(SRC_DIR) $< > $(BUILD_DIR)$*.d
###########################

clean:
	@rm -rf $(BIN)
	@rm -rf $(BUILD_DIR)

test:
	@echo $(CXXFLAGS)

.PHONY: all clean test