SRC=local.max.c

CC=gcc
INC=../include
UTIL=$(INC)/clutil.c
OBJ=$(SRC:.c=.o) $(UTIL:.c=.o)
SRCCL=$(SRC:.c=.cl)
TARGET=$(SRC:.c=.out)
CFLAG=-lOpenCL -g -I$(INC) -lm
INPUT=input/local.max.8.in 8
INPUT2=input/local.max.24.in 24

all: $(TARGET)

$(TARGET): $(OBJ) $(SRCCL)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAG)

$(SRC:.c=.o): $(SRC)
	$(CC) -c $(SRC) $(CFLAG)

$(UTIL:.c=.o): $(UTIL)
	$(CC) -c -o $(UTIL:.c=.o) $(UTIL) $(CFLAG)

run:
	./$(TARGET) $(INPUT)

clean:
	rm -rf $(OBJ) $(TARGET)
