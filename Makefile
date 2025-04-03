# ==== CONFIGURATION ====

BUILD_TYPE ?= mpi
EXEC_BASE = nerdss_$(BUILD_TYPE)
EXEC = bin/$(EXEC_BASE)
MAIN_SRC = EXEs/$(EXEC_BASE).cpp

SRC_DIRS = src src/boundary_conditions src/classes src/io src/math src/parser \
           src/reactions src/system_setup src/trajectory_functions src/error src/debug src/mpi
VPATH := $(SRC_DIRS)

OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIRS = -Iinclude $(shell gsl-config --cflags)
LIBS = $(shell gsl-config --libs)

CXX ?= g++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra
LDFLAGS =

ifdef ENABLE_PROFILING
    CXXFLAGS += -DENABLE_PROFILING -g
    LIBS += -lprofiler
endif

ifeq ($(BUILD_TYPE),mpi)
    CXX := mpicxx
    CXXFLAGS += -Dmpi_
endif

ifeq ($(BUILD_TYPE),omp)
    CXXFLAGS += -fopenmp -DOMP
endif

# ==== OBJECTS ====

SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))
DEPS := $(OBJECTS:.o=.d)

# ==== TEST CONFIG ====

GTEST_DIR = external/googletest/googletest
GTEST_SRC = $(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJ = $(OBJ_DIR)/gtest-all.o
GTEST_INC = -I$(GTEST_DIR) -I$(GTEST_DIR)/include
TEST_SRC = $(wildcard test/test_*.cpp)
TEST_OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(TEST_SRC)))
TEST_EXEC = test/test_runner

# ==== TARGETS ====

.PHONY: all serial mpi omp test clean

all: $(EXEC)

serial:
	$(MAKE) BUILD_TYPE=serial

mpi:
	$(MAKE) BUILD_TYPE=mpi

omp:
	$(MAKE) BUILD_TYPE=omp

test: $(TEST_EXEC)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) test/test_runner *.dSYM

# ==== MAIN BUILD RULE ====

$(EXEC): $(MAIN_SRC) $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LIBS)

# ==== TEST BUILD RULES ====

$(TEST_EXEC): $(TEST_OBJS) $(GTEST_OBJ) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $(GTEST_INC) -pthread $^ -o $@ $(LIBS)

$(GTEST_OBJ): $(GTEST_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $< -o $@

# Compile object files from test sources
$(OBJ_DIR)/%.o: test/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $(GTEST_INC) -MMD -MP -c $< -o $@

# Compile object files from simulation sources
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -MMD -MP -c $< -o $@

-include $(DEPS)

# ==== DIRECTORIES ====

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)