# CMPS 3600 Week 03
# Makefile for code in /examples/week03

all:	sigmask sighand1 sighand2 perror sighand3 readwrite handler_masks startstop

# demonstrates open and fopen
readwrite:	readwrite.c
	gcc -o readwrite readwrite.c

# this source demonstrates sending signals
sigmask:	sigmask.c
	gcc -o sigmask sigmask.c

# this source demonstrates simple signal handling 
sighand1:	sighand1.c 
	gcc -o sighand1 sighand1.c

# demonstrates signal handling within a signal handler
sighand2:	sighand2.c 
	gcc -o sighand2 sighand2.c

# demonstrates use of perror
perror:	perror.c 
	gcc -o perror perror.c

# demonstrates signals from parent - child and handler 
sighand3:	sighand3.c 
	gcc -o sighand3 sighand3.c

handler_masks:  handler_masks.c
	gcc -o handler_masks handler_masks.c

startstop:  startstop.c
	gcc -o startstop startstop.c

clean:  # start from scratch 
	rm -f *.o
	rm -f sigmask sighand1 sighand2 perror sighand3 readwrite handler_masks startstop
