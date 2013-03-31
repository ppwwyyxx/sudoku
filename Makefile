
# $File: Makefile
# $Date: Sun Mar 31 13:36:48 2013 +0800

OBJ_DIR = obj
TARGET = bin/main

INCLUDE_DIR = -Isrc/include
#DEFINES = -DDEBUG
OPTFLAGS = -O3
CXXFLAGS = $(INCLUDE_DIR) $(DEFINES) $(OPTFLAGS)
LDFLAGS =

CC = g++
SHELL = bash
ccSOURCES = $(shell find src -name "*.cc" | sed 's/^\.\///g')
OBJS = $(addprefix $(OBJ_DIR)/,$(ccSOURCES:.cc=.o))
DEPFILES = $(OBJS:.o=.d)

.PHONY: all clean run test bin

all: $(TARGET)

sinclude $(DEPFILES)

$(OBJ_DIR)/%.o: %.cc Makefile
	@echo "[cc] $< ..."
	@$(CC) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.d: %.cc
	@mkdir -p $(dir $@)
	@echo "[dep] $< ..."
	@$(CC) $(INCLUDE_DIR) $(DEFINES) -MM -MT "$(OBJ_DIR)/$(<:.cc=.o) $(OBJ_DIR)/$(<:.cc=.d)" "$<"  > "$@"


$(TARGET): $(OBJS) bin
	@echo "Linking ..."
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "done."

bin:
	@mkdir -pv bin


clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
	@rm -rf bin

run: $(TARGET)
	./$(TARGET)

test:
	./test/test.sh $(TARGET)
