#  Copyright Matthias Troyer 2009 - 2010.
#  Distributed under the Boost Software License, Version 1.0.
#      (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

## Change ALPS_ROOT if you have installed ALPS in another location
ALPS_ROOT = /Users/ricoh/Applications/alps

include $(ALPS_ROOT)/share/alps/include.mk

all: heisenberg

heisenberg: heisenberg.o main.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ heisenberg.o main.o $(LDFLAGS) -L/usr/local/Cellar/boost/1.53.0/lib -lalps -lboost_python-mt -lboost_system-mt -lboost_filesystem-mt $(PYTHON_LIBS)
run:
	./heisenberg -T 15 param.txt
clean:
	$(RM) $(RMFLAGS) *.o heisenberg param.clone0.h5 param.out.h5
