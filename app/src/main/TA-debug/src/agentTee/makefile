
SRC :=  $(wildcard ./*.c)
SRC +=  $(wildcard ./src/*.c)

COBJS := $(SRC:%.c=%.o)

TARGET = $(COBJS)

ifeq ($(TOOL_CHAIN),1)
       CC = $(ARM_GCC_TOOL_PATH)arm-none-eabi-gcc
       LD = $(ARM_GCC_TOOL_PATH)arm-none-eabi-ld
else
       CC = $(ARM_GCC_TOOL_PATH)arm-eabi-gcc
       LD = $(ARM_GCC_TOOL_PATH)arm-eabi-ld
endif

CFLAGS := -O -W -Wall -Werror
CFLAGS += -fno-short-enums
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -fstack-protector -Wstack-protector --param ssp-buffer-size=4
CFLAGS += -frecord-gcc-switches
CFLAGS += -Wextra -nostdinc -nodefaultlibs
CFLAGS += -march=armv8-a -marm -Os -fno-peephole -fno-peephole2 -Wno-main -fPIC
CFLAGS += -Wno-error=unused-parameter -Wno-error=unused-but-set-variable
-include ./config.mk

INCLUDEDIR := -I../../include \
	-I../../include/huawei_ext/ \
	-I../../include/huawei_ext/libc \
	-I../../include/huawei_ext/libc/arch/arm/bits \
	-I../../include/huawei_ext/libc/arch/generic \
	-I../../include/huawei_ext/libc/arch/arm \
	-I./include

DYN_LINK := y

ifeq ($(DYN_LINK),y)
EXTRAO := ../../release/lib/elf_main_entry_dyn.o
LDFLAGS += -s -z text -z now -z relro -shared -e tee_task_entry
LDFLAGS += -L../../release/lib -lc_shared_a32
LDFLAGS += -T../../release/lib/ta_link_dyn.ld
else
EXTRAO := ../../release/lib/elf_main_entry.o
LDFLAGS += -r -d
LDFLAGS += -T../../release/lib/ta_link.ld
endif

combine: $(TARGET)
	$(LD) $(LDFLAGS) $(TARGET) $(EXTRAO) -o combine.o

src/%.o: ./src/%.c
	$(CC) $(CFLAGS)  $(INCLUDEDIR) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS)  $(INCLUDEDIR) -c $< -o $@

clean:
	rm -f *.o src/*.o
