SRC=median.filter.c

CC=gcc
INC=./include
UTIL=$(INC)/clutil.c
OBJ=$(SRC:.c=.o) $(UTIL:.c=.o)
SRCCL=$(SRC:.c=.cl)
TARGET=$(SRC:.c=.out)
CFLAG=-lOpenCL -g -I$(INC) -lm
INPUT=../input.11.dat 11

all: $(TARGET)

$(TARGET): $(OBJ) $(SRCCL)
	$(CC) $(CFLAG) test.data.gen.c -o test.data.gen.out
	$(CC) $(OBJ) -o $(TARGET) $(CFLAG)

$(SRC:.c=.o): $(SRC)
	$(CC) -c $(SRC) $(CFLAG)

$(UTIL:.c=.o): $(UTIL)
	$(CC) -c -o $(UTIL:.c=.o) $(UTIL) $(CFLAG)

run:
	./$(TARGET) $(INPUT)

clean:
	rm -rf $(OBJ) $(TARGET) *.out
