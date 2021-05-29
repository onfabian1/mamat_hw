CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -L. -Wextra
CCLINK = $(CXX)
RM = rm -fr *.o firewall.exe libfirewall.so
NEW_LIB = firewall
PROG = firewall.exe
CPP_FILES = field.cpp ip.cpp port.cpp string.cpp
MAIN = main.cpp


all:$(PROG)
$(NEW_LIB):	
	$(CCLINK) $(CXXFLAGS) -fPIC -shared $(CPP_FILES) -o lib$(NEW_LIB).so

$(PROG): $(NEW_LIB)
	$(CCLINK) $(CXXFLAGS) $(MAIN) -o $(PROG) lib$(NEW_LIB).so -linput		

	
clean:
	$(RM)



