CC			=	clang
CFLAGS		=	-Wall -Wextra -Wall

INCLUDES	=	-I. -I./libft

.PHONY: ft

all: ft
	$(CC) -g server.c ./libft/libft.a $(INCLUDES) -o server
	$(CC) -g client.c ./libft/libft.a $(INCLUDES) -o client

ft:
	make -C libft