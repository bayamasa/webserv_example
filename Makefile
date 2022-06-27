# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 18:47:47 by mhirabay          #+#    #+#              #
#    Updated: 2022/06/27 22:03:53 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= webserv

UTILS_DIR		:= utils/
UTILS_SRCNAME	:= args_handling.cpp
UTILS_SRCS		:= $(addprefix $(UTILS_DIR), $(UTILS_SRCNAME))

CONF_DIR		:= conf/
CONF_SRCNAME	:= ConfigOptionConstant.cpp ConfigReader.cpp Config.cpp 
CONF_SRCS		:= $(addprefix $(CONF_DIR), $(CONF_SRCNAME))

CONTEXT_DIR		:= context/
CONTEXT_SRCNAME	:= Context.cpp
CONTEXT_SRCS	:= $(addprefix $(CONTEXT_DIR), $(CONTEXT_SRCNAME))

SOCKET_DIR		:= socket/
SOCKET_SRCNAME	:= Socket.cpp
SOCKET_SRCS		:= $(addprefix $(SOCKET_DIR), $(SOCKET_SRCNAME))

SERVER_DIR		:= server/
SERVER_SRCNAME	:= Selector.cpp
SERVER_SRCS		:= $(addprefix $(SERVER_DIR), $(SERVER_SRCNAME))



SRCS			:=	main.cpp init.cpp event.cpp \
					$(UTILS_SRCS) \
					$(CONF_SRCS) \
					$(CONTEXT_SRCS) \
					$(SOCKET_SRCS) \
					$(SERVER_SRCS) \

CXX				:= c++
RM				:= rm -rf
INC				:= -I . \
					-I ./$(CONF_DIR) \
					-I ./$(CONTEXT_DIR) \
					-I ./$(UTILS_DIR) \
					-I ./$(SOCKET_DIR) \
					-I ./$(SERVER_DIR) \

CXXFLAGS		:= -Wall -Wextra -Werror -std=c++98 $(INC) -pedantic -Wshadow


OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCS:%.cpp=%.o))

SRCSDIR := ./

all:			$(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(OBJS) : $(OBJSDIR)

$(OBJSDIR)%.o : ./%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@


$(OBJSDIR):
	mkdir -p $(OBJSDIR)
	mkdir -p $(OBJSDIR)$(CONF_DIR)
	mkdir -p $(OBJSDIR)$(UTILS_DIR)
	mkdir -p $(OBJSDIR)$(CONTEXT_DIR)
	mkdir -p $(OBJSDIR)$(SOCKET_DIR)
	mkdir -p $(OBJSDIR)$(SERVER_DIR)
	

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJSDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
