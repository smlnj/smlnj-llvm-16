# Makefile
#
# COPYRIGHT (c) 2023 The Fellowship of SML/NJ (http://www.smlnj.org)
# All rights reserved.
#
# Makefile for compiling the `cfgc` test driver
#

SHELL =		/bin/sh

TARGET =	cfgc

# determine the host architecture; we use the LLVM triple
# names, which are different from the names that llvm-config
# reports.
#
UNAME_ARCH :=	$(shell uname -m)
ifeq ($(UNAME_ARCH),x86_64)
HOST_ARCH="x86_64"
else ifeq ($(UNAME_ARCH),arm64)
HOST_ARCH="aarch64"
else
HOST_ARCH=unknown
endif

LLVM_DIR =	../..
LLVM_CONFIG =	$(LLVM_DIR)/bin/llvm-config

LLVM_TARGETS = $(shell $(LLVM_CONFIG) --targets-built)
LLVM_CPP_FLAGS := $(shell $(LLVM_CONFIG) --cppflags)
LLVM_LD_FLAGS := $(shell $(LLVM_CONFIG) --ldflags)
LLVM_LIBS :=	$(shell $(LLVM_CONFIG) --libs $(LLVM_TARGETS) passes) \
		$(shell $(LLVM_CONFIG) --system-libs)
LLVM_BUILD_MODE := $(shell $(LLVM_CONFIG) --build-mode)

# determine the operating system
#
HOST_OS := $(shell uname -s)
ifeq ($(HOST_OS),Darwin)
TARGET_FLAGS += -DOPSYS_DARWIN
else ifeq ($(HOST_OS),Linux)
TARGET_FLAGS += -DOPSYS_LINUX
endif

# determine the supported targets
#
ifneq (,$(findstring AArch64,$(LLVM_TARGETS)))
TARGET_FLAGS +=	-DENABLE_ARM64
endif
ifneq (,$(findstring X86,$(LLVM_TARGETS)))
TARGET_FLAGS +=	-DENABLE_X86
endif

CXX =		clang++ --std=c++17
CPP_FLAGS =	-I../include -I$(LLVM_DIR)/include/
CXX_FLAGS =	-g $(LLVM_CXX_FLAGS)
LD_FLAGS =	$(LLVM_LD_FLAGS)

INCLUDES =	$(wildcard ../include/*hpp) $(wildcard ../include/asdl/*hpp)
SRCS =		$(wildcard *.cpp)
OBJS =		$(SRCS:%.cpp=%.o)

$(TARGET):	$(OBJS)
	clang++ -o $(TARGET) $(LD_FLAGS) $(OBJS) $(LLVM_LIBS)

%.o: %.cpp $(INCLUDES)
	$(CXX) -c -DHOST_ARCH="\"$(HOST_ARCH)\"" $(CPP_FLAGS) $(CXX_FLAGS) $(TARGET_FLAGS) $<

.PHONY:		install
install:	$(TARGET)
	cp -p $(TARGET) $(LLVM_DIR)/bin/

.PHONY:		clean
clean:
		rm -rf $(OBJS) $(TARGET)
