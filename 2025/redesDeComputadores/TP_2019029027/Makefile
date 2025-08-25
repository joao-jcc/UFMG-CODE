CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SERVER_SRC = src/server.c src/common.c
SENSOR_SRC = src/sensor.c src/common.c

all: server sensor

server: $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

sensor: $(SENSOR_SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f server sensor
