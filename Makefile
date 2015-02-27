##########################################################################
# Setup

PROJECT = ADS1015
CC = g++ 
CFLAGS =
INCDIR =

SRC  = \
    test.cpp \
    ADS1015.cpp \
    I2C.cpp \
    
OBJS = $(SRC:.cpp=.o)

##########################################################################
# Targets

all: $(OBJS) $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) -o $(PROJECT) $(OBJS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) -I. $(INCDIR) $< -o $@
	
clean:
	rm -f $(OBJS)
	rm -f $(PROJECT)