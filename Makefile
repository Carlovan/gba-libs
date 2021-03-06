BINPATH := $(realpath ../SDK/devkitARM/bin)
PATH := $(BINPATH):$(PATH)

# --- Project details -------------------------------------------------

TARGET  := test

OBJS    := $(TARGET).o
LIBS_S  := $(wildcard libs/sources/*.cpp)
LIBS_B  := $(addprefix libs/bin/, $(notdir $(LIBS_S)))
LIBS_B  := $(LIBS_B:.cpp=.o)

# --- Build defines ---------------------------------------------------

PREFIX  := arm-none-eabi-
export CC      := $(PREFIX)gcc
export LD      := $(PREFIX)gcc
export OBJCOPY := $(PREFIX)objcopy

ARCH    := -mthumb-interwork -mthumb
SPECS   := -specs=gba.specs

export CFLAGS  := $(ARCH) -Wall -fno-strict-aliasing
export LDFLAGS := $(ARCH) $(SPECS)


.PHONY : build clean libs

# --- Build -----------------------------------------------------------
# Build process starts here!

build: $(TARGET).gba

# Strip and fix header (step 3,4)
$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@

# Link (step 2)
$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LIBS_B) $(LDFLAGS) -o $@

$(LIBS_B): $(LIBS_S)
	make libs

# Compile (step 1)
$(OBJS) : %.o : %.cpp $(wildcard h/*)
	$(CC) -c $< $(CFLAGS) -o $@
		
# --- Clean -----------------------------------------------------------

clean : 
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

cleanlibs:
	@rm -fv libs/bin/*

#---- Compile libraries ------------------------------------
libs:
	mkdir -p libs/bin
	cd libs && $(MAKE)
#EOF
