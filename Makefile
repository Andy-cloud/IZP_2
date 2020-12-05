C=gcc
CFLAGS= -std=c99 -Wall -Wextra -Werror
CNAME=sps.c
NAME=sps

c:
	$(CC) $(CFLAGS) $(CNAME) -o $(NAME)
v:
	clear
	valgrind --leak-check=full ./$(NAME) -d : '[,3];acol;[1,];swap [1,4];inc 0;[2,];swap [2,4];[2,1];use _0;inc 0;[3,];swap [3,4];[3,1];use _0;inc 0;[4,];swap [4,4];[4,1];use _0' text3.txt
r:
	./$(NAME) -d : a text3.txt
cv:
	clear
	$(CC) $(CFLAGS) -g $(CNAME) -o $(NAME)
	valgrind --leak-check=full ./$(NAME) -d : '[3,3];irow;icol' text3.txt
d:
	clear
	$(CC) $(CFLAGS) -g $(CNAME) -o $(NAME)
	gdb -tui $(NAME)
cr: 
	clear
	$(CC) $(CFLAGS) $(CNAME) -o $(NAME)
	./$(NAME) -d : '[,3];acol;[1,_];swap [1,4];inc 0;[2,];swap [2,4];[2,1];use _0;inc 0;[3,];swap [3,4];[3,1];use _0;inc 0;[4,];swap [4,4];[4,1];use _0' text3.txt
