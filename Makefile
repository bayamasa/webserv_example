# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 18:47:47 by mhirabay          #+#    #+#              #
#    Updated: 2022/06/16 17:30:04 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


UTILS_DIR		= utils/
UTILS_SRCNAME	= args_handling.cpp

UTILS_SRCS		= $(addprefix $(UTILS_DIR), $(UTILS_SRCNAME))

SRCS			=	main.cpp \
					$(UTILS_SRCS)

OBJS			= $(SRCS:.cpp=.o)

CXX				= c++
RM				= rm -f
INC				= -I ./$(UTILS_DIR)
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic -Wshadow

NAME			= a.out

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
