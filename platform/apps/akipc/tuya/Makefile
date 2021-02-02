CC = arm-anykav200-linux-uclibcgnueabi-cc

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

CFLAGS += -I./ -I./include -L./lib  -ltuya_ipc -lpthread -lm -lrt -ldl -lstdc++ -ltuya_p2p -lz
WIFI_IPC=1
ifeq ($(WIFI_IPC), 1)
CFLAGS += -DWIFI_IPC=1
endif
.PHONY: all install

all: $(OBJS)
	@mv *.o $(TARGET_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo ""

install:
	@echo ""
