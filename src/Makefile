CC = g++
CFLAGS = -g -Wall 
#LINKS = 
TARGET = chatbot
SRC_FILES = $(wildcard *.cpp)
OBJS = ${SRC_FILES:.c=.o}

all:
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
