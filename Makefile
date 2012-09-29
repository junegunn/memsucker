# Junegunn Choi (junegunn.c@gmail.com)
# 2012/09/30-

SRC     = $(wildcard *.cc)
CFLAGS  = -O2 -Wall

#-------------------------------------------------

EXEC    = $(basename $(SRC))
CFLAGS += $(addprefix -I, $(INCLUDE))

all: $(EXEC)

%: %.cc
	g++ $@.cc $(CFLAGS) -o $@

install:
	cp $(EXEC) ~/bin

clean:
	-rm -vf $(EXEC)

.PHONY: clean all

#------------------------------------------------

