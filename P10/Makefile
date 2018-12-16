CC = gcc
CC_FLAGS = -g 
OBJS = graph.o challenge.o utils.o

.c.o:
		$(CC) $(CC_FLAGS) -c $<

challenge: graph.o challenge.o 
				$(CC) -o challenge $(OBJS)

clean:
		rm *.o 
		rm challenge