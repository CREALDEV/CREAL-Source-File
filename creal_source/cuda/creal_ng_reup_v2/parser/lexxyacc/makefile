YFLAGS			= -d

PROGRAM			= creal_p

OBJS			= mainyacc.tab.o lex.yy.o

SRCS			= mainyacc.tab.c lex.yy.c

CC				= gcc

all:			$(PROGRAM)

.c.o:			$(SRCS)
				$(CC) -c $*.c -o $@ -O
				
mainyacc.tab.c: mainyacc.y
				 bison $(YFLAGS) mainyacc.y
				 
lex.yy.c:		 mainlex.l
				 flex mainlex.l
creal_p:		 $(OBJS)
				 $(CC) $(OBJS) -o $@ -lfl -lm

clean :;		 @echo "cleaning up"
				 rm *.o *.c *.h 
				 
				 
