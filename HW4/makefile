CC     = gcc
CFLAGS = -Wall -g -std=c99 
CCLINK = $(CC)
RM = rm -fr *.o libgrades.so
EXEC = prog1.exe
	

	export LD_LIBRARY_PATH=/home/mamat/mamat_hw/HW4:$LD_LIBRARY_PATH

	
libgrades.so: grades.o 
	$(CCLINK) -shared grades.o -o libgrades.so -L. -llinked-list
	
grades.o: grades.c linked-list.h 
			$(CC) $(CFLAGS) -c grades.c -fPIC -llinked-list			

	
$(EXEC): libgrades.so
	$(CCLINK) libgrades.so -o $(EXEC) -llinked-list -L/home/mamat/mamat_hw/HW4 -lgrades -L/home/mamat/mamat_hw/HW4

	
clean:
	$(RM)		
			
	

	



	
	
	


