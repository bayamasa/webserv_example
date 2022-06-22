# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 18:47:47 by mhirabay          #+#    #+#              #
#    Updated: 2022/06/22 21:57:31 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= webserv

UTILS_DIR		:= utils/
UTILS_SRCNAME	:= args_handling.cpp

UTILS_SRCS		:= $(addprefix $(UTILS_DIR), $(UTILS_SRCNAME))

CONF_DIR		:= conf/
CONF_SRCNAME	:= ConfigConstant.cpp ConfigReader.cpp Config.cpp 

CONF_SRCS		:= $(addprefix $(CONF_DIR), $(CONF_SRCNAME))

CONTEXT_DIR		:= context/
CONTEXT_SRCNAME	:= Context.cpp

CONTEXT_SRCS	:= $(addprefix $(CONTEXT_DIR), $(CONTEXT_SRCNAME))


SRCS			:=	main.cpp \
					$(UTILS_SRCS) \
					$(CONF_SRCS) \
					$(CONTEXT_SRCS) 

CXX				:= c++
RM				:= rm -rf
INC				:= -I . \
					-I ./$(CONF_DIR) \
					-I ./$(CONTEXT_DIR) \
					-I ./$(UTILS_DIR)

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
	

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJSDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
