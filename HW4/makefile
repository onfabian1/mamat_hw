CC     = gcc
CFLAGS = -Wall -g -std=c99
CCLINK = $(CC)
RM = rm -fr *.o libgrades.so


libgrades.so: grades.o 
	$(CCLINK) -shared grades.o -o -llinked-list -L.
	
grades.o: grades.c linked-list.h
			$(CC) $(CFLAGS) -c grades.c 
clean:
	$(RM)
