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

# Detecting operating system (both MacOS and Linux supported)
UNAME_S = $(shell uname -s)

ifdef DEBUG
$(info ->Debugging symbols enabled) 
    CXXFLAGS += -g
	LDFLAGS += $(shell pkg-config libzip --libs)
	BIN_DIR = bin/
else
$(info ->Release mode)
    CXXFLAGS += -O3
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS += -undefined dynamic_lookup
	endif
endif


CXXFLAGS += $(shell pkg-config libzip --cflags)
LDFLAGS += $(shell pkg-config libzip --libs)

COMPILE_COMMAND_CORE = $(CXX) $(CXXFLAGS)

# Directories:
SRC_CORE_DIR = src/core/

BUILD_DIR_CORE = build/

# Source files:
SRC_CORE  = *.cpp */*.cpp */*/*.cpp
SRC_CORE := $(addprefix $(SRC_CORE_DIR), $(SRC_CORE))
SRC_CORE := $(wildcard $(SRC_CORE))

# Object files:
OBJ_CORE := $(basename $(SRC_CORE))
OBJ_CORE := $(subst $(SRC_CORE_DIR), ,$(OBJ_CORE))
OBJ_CORE := $(addsuffix .o, $(OBJ_CORE))
OBJ_CORE := $(addprefix $(BUILD_DIR_CORE), $(OBJ_CORE))

# Dependency files:
DEPENDENCIES_CORE := $(OBJ_CORE)
DEPENDENCIES_CORE := $(basename $(DEPENDENCIES_CORE))
DEPENDENCIES_CORE := $(addsuffix .d, $(DEPENDENCIES_CORE))



# Binary output:
BIN_CORE = $(BIN_DIR)greta.so
BIN_LUA = $(BIN_DIR)greta_lua.so
BIN_PYTHON = $(BIN_DIR)py_greta.so

all: core lua python

core: $(BIN_CORE)

lua: $(BIN_LUA)

python: $(BIN_PYTHON)


###########################
$(BIN_CORE): $(OBJ_CORE)
	@echo -Linking libgreta
	@mkdir -p $(dir $@) >/dev/null
	@$(CXX) $^ $(LDFLAGS) -o $@

###########################
-include $(DEPENDENCIES_CORE)

$(BUILD_DIR_CORE)%.o: $(SRC_CORE_DIR)%.cpp
	@echo -Compiling $<
	@mkdir -p $(dir $@) >/dev/null
	@$(COMPILE_COMMAND_CORE) -I$(SRC_CORE_DIR) -o $@ -c $<
	@$(COMPILE_COMMAND_CORE) -MM -MT $@ -I$(SRC_CORE_DIR) $< > $(BUILD_DIR_CORE)$*.d
###########################



BUILD_DIR_LUA = build/lua/
SRC_LUA_DIR = src/bindings/lua/

SRC_LUA  = *.cpp */*.cpp */*/*.cpp
SRC_LUA := $(addprefix $(SRC_LUA_DIR), $(SRC_LUA))
SRC_LUA := $(wildcard $(SRC_LUA))

# Object files:
OBJ_LUA := $(basename $(SRC_LUA))
OBJ_LUA := $(subst $(SRC_LUA_DIR), ,$(OBJ_LUA))
OBJ_LUA := $(addsuffix .o, $(OBJ_LUA))
OBJ_LUA := $(addprefix $(BUILD_DIR_LUA), $(OBJ_LUA))

# Dependency files:
DEPENDENCIES_LUA := $(OBJ_LUA)
DEPENDENCIES_LUA := $(basename $(DEPENDENCIES_LUA))
DEPENDENCIES_LUA := $(addsuffix .d, $(DEPENDENCIES_LUA))


# Warnings:
CXXFLAGS_LUA += -Wall

# Standart:
CXXFLAGS_LUA += --std=c++17 -fPIC

CXXFLAGS_LUA += $(shell pkg-config lua --cflags)
LDFLAGS_LUA += $(shell pkg-config lua --libs)
# Compiling to dll
LDFLAGS_LUA += -shared -Wl,-rpath,'$$ORIGIN'

COMPILE_COMMAND_LUA = $(CXX) $(CXXFLAGS_LUA)

###########################
$(BIN_LUA): $(OBJ_LUA) $(BIN_CORE)
	@echo -Linking libgreta_lua
	@mkdir -p $(dir $@) >/dev/null
	@$(CXX) $^ $(LDFLAGS_LUA) $(BIN_CORE) -o $@

###########################
-include $(DEPENDENCIES_LUA)

$(BUILD_DIR_LUA)%.o: $(SRC_LUA_DIR)%.cpp
	@echo -Compiling $<
	@mkdir -p $(dir $@) >/dev/null
	@$(COMPILE_COMMAND_LUA) -I$(SRC_CORE_DIR) -I$(SRC_LUA_DIR) -o $@ -c $<
	@$(COMPILE_COMMAND_LUA) -MM -MT $@ -I$(SRC_CORE_DIR) -I$(SRC_LUA_DIR) $< > $(BUILD_DIR_LUA)$*.d
###########################


BUILD_DIR_PYTHON = build/python/
SRC_PYTHON_DIR = src/bindings/python/

SRC_PYTHON  = *.cpp */*.cpp */*/*.cpp
SRC_PYTHON := $(addprefix $(SRC_PYTHON_DIR), $(SRC_PYTHON))
SRC_PYTHON := $(wildcard $(SRC_PYTHON))

# Object files:
OBJ_PYTHON := $(basename $(SRC_PYTHON))
OBJ_PYTHON := $(subst $(SRC_PYTHON_DIR), ,$(OBJ_PYTHON))
OBJ_PYTHON := $(addsuffix .o, $(OBJ_PYTHON))
OBJ_PYTHON := $(addprefix $(BUILD_DIR_PYTHON), $(OBJ_PYTHON))

# Dependency files:
DEPENDENCIES_PYTHON := $(OBJ_PYTHON)
DEPENDENCIES_PYTHON := $(basename $(DEPENDENCIES_PYTHON))
DEPENDENCIES_PYTHON := $(addsuffix .d, $(DEPENDENCIES_PYTHON))


# Warnings:
CXXFLAGS_PYTHON += -Wall

# Standart:
CXXFLAGS_PYTHON += --std=c++17 -fPIC

CXXFLAGS_PYTHON += $(shell pkg-config python3 --cflags)
# LDFLAGS_PYTHON += $(shell pkg-config python3 --libs)
# Compiling to dll
LDFLAGS_PYTHON += -shared -Wl,-rpath,'$$ORIGIN'

COMPILE_COMMAND_PYTHON = $(CXX) $(CXXFLAGS_PYTHON)

###########################
$(BIN_PYTHON): $(OBJ_PYTHON) $(BIN_CORE)
	@echo -Linking libgreta_python
	@mkdir -p $(dir $@) >/dev/null
	@$(CXX) $^ $(LDFLAGS_PYTHON) $(BIN_CORE) -o $@

###########################
-include $(DEPENDENCIES_PYTHON)

$(BUILD_DIR_PYTHON)%.o: $(SRC_PYTHON_DIR)%.cpp
	@echo -Compiling $<
	@mkdir -p $(dir $@) >/dev/null
	@$(COMPILE_COMMAND_PYTHON) -I$(SRC_CORE_DIR) -I$(SRC_PYTHON_DIR) -o $@ -c $<
	@$(COMPILE_COMMAND_PYTHON) -MM -MT $@ -I$(SRC_CORE_DIR) -I$(SRC_PYTHON_DIR) $< > $(BUILD_DIR_PYTHON)$*.d
###########################



clean:
	@rm -rf $(BIN_CORE)
	@rm -rf $(BIN_LUA)
	@rm -rf $(BUILD_DIR_CORE)
	@rm -rf $(BUILD_DIR_LUA)
	@rm -rf $(BUILD_DIR_PYTHON)
	@em -rf $(BIN_PYTHON)

test:
	@echo $(CXXFLAGS)

.PHONY: all core lua python clean test