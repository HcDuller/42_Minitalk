CC			=	clang
CFLAGS		=	-Wall -Wextra -Wall

INCLUDES	=	-I. -I./libft
LIBS		=	./libft/libft.a

SERVER_RAW	=	server.c server_utils.c
CLIENT_RAW	=	client.c client_utils.c

SERVER_OBJ	=	$(SERVER_RAW:.c=.o)
CLIENT_OBJ	=	$(CLIENT_RAW:.c=.o)

.PHONY: ft clean fclean re

all: ft server client

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBS) $(INCLUDES) -o server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBS) $(INCLUDES) -o client

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make clean -C libft

fclean: clean
	@rm -f server client
	make fclean -C libft

ft:
	make -C libft

re: fclean all