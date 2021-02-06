##
# Pong Clock
#
# @file
# @version 0.1
TARGET_EXEC ?= tty-pong-clock

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

LDFLAGS =  -lncursesw -lstdc++ -lm
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

# CC=gcc
# CXX=g++
# RM=rm -f
# CPPFLAGS=-g $(shell root-config --cflags)
# LDFLAGS=-g $(shell root-config --ldflags)
# LDLIBS=$(shell root-config --libs)

# SRCS=main.cpp matrix.cpp
# OBJS=$(subst .cc,.o,$(SRCS))

# all: pong

# pong: $(OBJS)
#     $(CXX) $(LDFLAGS) -o pong $(OBJS) $(LDLIBS)

# pong.o: tool.c support.hh

# clean:
#     $(RM) $(OBJS)

# distclean: clean
#     $(RM) pong
# PKGCONFIG = $(shell which pkg-config)
# CPPFLAGS = -O2 #$(shell $(PKGCONFIG))
# CPPFLAGS_DBG = -g -O0 -DDEBUG -DDEBUG_EV $(CFLAGS)
# LDFLAGS =  -lncursesw
# PREFIX=/opt
# BIN = $(PREFIX)/bin

# MANDIR = $(PREFIX)/man/man1
# MANSUFFIX = 1

# SRCS = main.cpp
# SRCS_DBG = main.cpp
# OBJS = $(SRCS:.cpp=.o)
# OBJS_DBG = $(SRCS_DBG:.c=.g)
# HDRS = main.h

# all: pong

# debug: pong.dbg

# .SUFFIXES : .g

# .c.g:
# 	g++ $(CPPFLAGS_DBG) -c $< -o $*.g

# pong.dbg: $(OBJS_DBG)
# 	g++ $(CPPFLAGS_DBG) -o $@ $(OBJS_DBG) $(LDFLAGS)

# pong: $(OBJS)
# 	g++ $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# $(OBJS): $(HDRS)

# $(OBJS_DBG): $(HDRS)

# # install: 9wm-xcb
# # 	cp 9wm-xcb $(BIN)/9wm

# # install.man:
# # 	cp 9wm.man $(MANDIR)/9wm.$(MANSUFFIX)

# # trout: 9wm.man
# # 	troff -man 9wm.man >trout

# # vu: trout
# # 	xditview trout

# clean:
# 	rm -f pong pong.dbg *.o *.g core

# # end

# # end
