HEAP_SIZE      = 8388208
STACK_SIZE     = 61800

PRODUCT = cstub.pdx

# Locate the SDK
SDK = /home/snic/PlaydateSDK

######
# IMPORTANT: You must add your source folders to VPATH for make to find them
# ex: VPATH += src1:src2
######

VPATH += src
VPATH += include

# List C source files here
SRC = $(wildcard src/*.c)

# List all user directories here
UINCDIR = include

# List user asm files
UASRC = 

# List all user C define here, like -D_DEBUG=1
UDEFS = -fsingle-precision-constant \
      -Wuninitialized -Wall -Wextra -pedantic-errors \
      -Wstrict-prototypes -Wshadow -Wundef -Wdouble-promotion \
      -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-variable \
      -Wno-unused-parameter
#      -Werror 

# Define ASM defines here
UADEFS = 

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

include $(SDK)/C_API/buildsupport/common.mk

# Override clean target to also remove cranehedLib object files
clean:
	@echo "detected_OS is \"$(detected_OS)\""
	rm -fR $(PRODUCT)
	rm -fR Source/pdex.bin
	rm -fR Source/pdex.dylib
	rm -fR Source/pdex.so
	rm -fR Source/pdex.dll
	rm -fR Source/pdex.elf

# Release build that strips debug symbols
release: all
	@echo "Stripping debug symbols..."
	-strip --strip-unneeded Source/pdex.so 2>/dev/null || true
	-arm-none-eabi-strip --strip-unneeded Source/pdex.elf 2>/dev/null || true
	@echo "Repacking with stripped binaries..."
	$(SDK)/bin/pdc -sdkpath $(SDK) Source $(PRODUCT)

# Install to device
install: release
	@echo "Mounting Playdate..."
	$(SDK)/bin/pdutil /dev/ttyACM0 datadisk
	@echo "Waiting for drive to mount..."
	sleep 4
	@echo "Installing to device..."
	rm -rf /media/snic/PLAYDATE/Games/$(PRODUCT)
	cp -r $(PRODUCT) /media/snic/PLAYDATE/Games/
	@echo "Installed!"