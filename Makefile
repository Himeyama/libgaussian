CC = gcc
LDSHARED = $(CC) -shared
SRCS = libgaussian.c
TARGET_SO = libgaussian.so
TARGET_H = gaussian.h

$(TARGET_SO): $(SRCS)
	$(LDSHARED) -o $@ $^ -fPIC -lm -I.

test: test.c
	$(CC) $^ -o $@ -L. -lgaussian -I.

install: $(TARGET_SO)
	mkdir -p $(ROOT)/lib
	mkdir -p $(ROOT)/include
	cp -v $(TARGET_SO) $(ROOT)/lib/$(TARGET_SO)
	cp -v $(TARGET_H) $(ROOT)/include/$(TARGET_H)