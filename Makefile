CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -lm
OBJ = main.o map.o pso.o logger.o utils.o
TARGET = pso.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del $(OBJ) $(TARGET)