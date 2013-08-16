
# $File: Makefile
# $Date: Fri Aug 16 17:19:46 2013 +0800

OBJ_DIR = obj
TARGET = main

INCLUDE_DIR = -Iinclude
#DEFINES = -DDEBUG
OPTFLAGS = -O3
CXXFLAGS = $(INCLUDE_DIR) $(DEFINES) $(OPTFLAGS) -std=c++11
LDFLAGS =

CC = g++
SHELL = bash
ccSOURCES = $(shell find -name "*.cc" | sed 's/^\.\///g')
OBJS = $(addprefix $(OBJ_DIR)/,$(ccSOURCES:.cc=.o))
DEPFILES = $(OBJS:.o=.d)

.PHONY: all clean run test

all: $(TARGET)

sinclude $(DEPFILES)

$(OBJ_DIR)/%.o: %.cc Makefile
	@echo "[cc] $< ..."
	@$(CC) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.d: %.cc
	@mkdir -p $(dir $@)
	@echo "[dep] $< ..."
	@$(CC) $(INCLUDE_DIR) $(DEFINES) -MM -MT "$(OBJ_DIR)/$(<:.cc=.o) $(OBJ_DIR)/$(<:.cc=.d)" "$<"  > "$@"


$(TARGET): $(OBJS)
	@echo "Linking ..."
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "done."


clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

test:
	../test/test.sh $(TARGET)
