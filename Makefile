CC = gcc
LDSHARED = $(CC) -shared
SRCS = libgaussian.c
TARGET_SO = libgaussian.so

$(TARGET_SO): $(SRCS)
	$(LDSHARED) -o $@ $^ -fPIC -lm -I.

test: test.c
	$(CC) $^ -o $@ -L. -lgaussian -I.