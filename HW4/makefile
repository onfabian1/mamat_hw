CC     = gcc
CFLAGS = -Wall -g -std=c99 
CCLINK = $(CC)
RM = rm -fr *.o libgrades.so

	
libgrades.so: grades.o 
	$(CCLINK) -shared grades.o -o libgrades.so -L. -llinked-list
	
grades.o: grades.c linked-list.h 
			$(CC) $(CFLAGS) -c grades.c -fPIC -llinked-list			

	
clean:
	$(RM)		
			
	

	



	
	
	


