CXX = g++
CXXFLAGS = -Wall -g -std=c+11 -L. -Wextra
CCLINK = $(CXX)
RM = rm -fr *.o firewall.exe firewall

CPP_FILES = field_new.cpp ip_new.cpp port_new.cpp string_new.cpp
MAIN = main_new.cpp

firewall:	
	$(CCLINK) $(CXXFLAGS) -fPIC -shared $(CPP_FILES) -o libfirewall.so


firewall.exe: firewall
	$(CCLINK) $(CXXFLAGS) $(MAIN) -o firewall.exe libfirewall.so -linput.so		

	
clean:
	$(RM)



