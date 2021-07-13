CLIENT = 	client
SERVER = 	server

SRCS_CL =	./srcs/client_folder/client_main.c \
			./srcs/utils.c

SRCS_SER = 	./srcs/server_folder/server_main.c \
			./srcs/utils.c

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -g -MMD
RM =		rm -rf

OBJS_SER =	${SRCS_SER:.c=.o}
OBJS_CL =	${SRCS_CL:.c=.o}
DOBJS_SER =	${SRCS_SER:.c=.d}
DOBJS_CL =	${SRCS_CL:.c=.d}


%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(CLIENT) $(SERVER)

$(CLIENT):	$(OBJS_CL)
			$(CC) $(FLAGS) $(OBJS_CL) -o $(CLIENT)

$(SERVER):	$(OBJS_SER)
			$(CC) $(FLAGS) $(OBJS_SER) -o $(SERVER)

clean:
			$(RM) $(OBJS_CL) $(DOBJS_CL)
			$(RM) $(OBJS_SER) $(DOBJS_SER)

fclean:		clean
			$(RM) $(CLIENT) $(SERVER)
			$(RM) $(SERVER)
			$(RM) $(CLIENT)

re:			fclean all

norm:		fclean
			norminette * 

.PHONY: all clean fclean re run bonus norm
#.SILENT:
-include $(DOBJS)

