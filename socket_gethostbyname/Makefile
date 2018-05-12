# 
TARGET = main
# 
OBJS = main.o

# 
CC=gcc
CFLAGS=-Wall -std=gnu99

$(TARGET):$(OBJS)
# @echo TARGET:$@
# @echo OBJECTS:$^
	$(CC) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS)