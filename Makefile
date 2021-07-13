SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -MMD

SRCS_SER = server/server_main.c
SRCS_CL = client/client_main.c
UTILS = ./utils.c

OBJS_SER = ${SRCS_SER:.c=.o}
OBJS_CL = ${SRCS_CL:.c=.o}
DOBJS_SER = ${SRCS_SER:.c=.d}
DOBJS_CL = ${SRCS_CL:.c=.d}

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

all: 		$(SERVER) $(CLIENT)

$(SERVER):	${OBJS_SER}
			$(CC) $(CFLAGS) ${OBJS_SER} -o $(SERVER)
			mv ../$(SERVER) $(SERVER)

$(CLIENT):	${OBJS_SER}
			$(CC) $(CFLAGS) ${OBJS_CL} -o $(CLIENT)
			mv ../$(CLIENT) $(CLIENT)

clean:		
			rm -rf $(OBJS_CL) $(DOBJS_CL)
			rm -rf $(OBJS_SER) $(DOBJS_SER)

fclean:		clean
			rm -rf $(CLIENT)
			rm -rf (SERVER)

re:			fclean all

norm:		fclean
			norminette ./*/*.c  

.PHONY: all clean fclean re run bonus 
#.SILENT:
-include $(DOBJS)
