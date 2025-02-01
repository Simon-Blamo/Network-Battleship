CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-Wall -g
LDFLAGS=-g -lpthread
LDLIBS=

C_SRCS=client.cpp
C_OBJS=$(subst .cpp,.o,$(C_SRCS))

S_SRCS=server.cpp
S_OBJS=$(subst .cpp,.o,$(S_SRCS))

all: client server

client: $(C_OBJS)
	$(CXX) $(LDFLAGS) -o client $(C_OBJS) $(LDLIBS)

server: $(S_OBJS)
	$(CXX) $(LDFLAGS) -o server $(S_OBJS) $(LDLIBS)


client.o: client.cpp network_packet.h grid.h
server.o: server.cpp network_packet.h grid.h

clean:
	$(RM) $(C_OBJS) $(S_OBJS)

distclean: clean
	$(RM) client server

