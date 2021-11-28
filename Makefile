CC = g++
CFLAGS = -O2
TARGET = main.out
OBJS = card.o person.o main.o

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o main.out
