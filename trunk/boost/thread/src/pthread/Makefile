# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
SRC_DIR := .
BUILD_ROOT_DIR := 
PRJ_ROOT_DIR := H:/svn/FIRST/boost
WS_ROOT_DIR := H:/svn/FIRST

ALL_BUILD_SPECS := PPC32diab PPC32gnu PPC603diab PPC603gnu
ENABLED_BUILD_SPECS := PPC603gnu

ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32diab_DEBUG
else
OBJ_DIR := PPC32diab
endif
endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32gnu_DEBUG
else
OBJ_DIR := PPC32gnu
endif
endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC603diab_DEBUG
else
OBJ_DIR := PPC603diab
endif
endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC603gnu_DEBUG
else
OBJ_DIR := PPC603gnu
endif
endif

DEP_FILES := $(OBJ_DIR)/exceptions.d $(OBJ_DIR)/once.d $(OBJ_DIR)/thread.d
-include $(DEP_FILES)

ifeq ($(BUILD_SPEC),PPC32diab)
SUBDIRS :=
OBJECTS := $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/once.o $(OBJ_DIR)/thread.o

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32gnu)
SUBDIRS :=
OBJECTS := $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/once.o $(OBJ_DIR)/thread.o

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC603diab)
SUBDIRS :=
OBJECTS := $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/once.o $(OBJ_DIR)/thread.o

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC603gnu)
SUBDIRS :=
OBJECTS := $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/once.o $(OBJ_DIR)/thread.o

PROJECT_TARGETS := $(OBJECTS)

SUB_OBJECTS :=
SUB_TARGETS :=
endif

PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0

ifeq ($(BUILD_SPEC),PPC32diab)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCFH:vxworks63 -Xstmw-slow -DPPC32_fp60x
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 
endif

ifeq ($(BUILD_SPEC),PPC32gnu)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mhard-float -mstrict-align -mno-implicit-fp -DPPC32_fp60x
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 
endif

ifeq ($(BUILD_SPEC),PPC603diab)
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC603FH:vxworks63
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 
endif

ifeq ($(BUILD_SPEC),PPC603gnu)
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip -IC:/Program\ Files/boost/boost_1_38_vxworks 

IDE_LIBRARIES = 
endif


ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -Wall  -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603diab)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC603gnu)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi   -xassembler-with-cpp -MD -MP $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"

endif





-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
