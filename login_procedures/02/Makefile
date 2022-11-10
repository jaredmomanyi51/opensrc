ALLCPP=$(wildcard *.cpp)
SOURCES=$(filter-out authlib.cpp,$(ALLCPP))
TARGETS=$(patsubst %.cpp,%,$(SOURCES))
CPPFLAGS= -O3 -finline-functions -Wall -pedantic -Wextra -Werror -Wno-deprecated-declarations -std=c++11
C=g++

all: $(TARGETS)

authlib.o: authlib.cpp
	$C $(CPPFLAGS) -c authlib.cpp

%: %.cpp authlib.o
	$C $(CPPFLAGS) $< authlib.o -lcrypto -o $@

clean:
	rm -f $(TARGETS)
	rm -f *~ *.o a.out
