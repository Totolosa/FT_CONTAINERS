RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
PINK    = \033[35m
CYAN    = \033[36m
WHITE   = \033[37m
END     = \033[0m
BOLD    = \033[1m
UNDER   = \033[4m
SUR     = \033[7m

NAME			= containers
INCLUDE			= vector.hpp
SRCS			= main.cpp
OBJS			= ${SRCS:%.cpp=$(DIR_OBJS)/%.o}
DIR_OBJS		= objs
COMPIL			= clang++
CPP_FLAGS		= -Wall -Wextra -Werror #-std=c++98
RM				= rm -rf
MKDIR			= mkdir -p

# all				: $(NAME)
all				: 
				@python3 TESTER_CONTAINERS42/tester.py

$(DIR_OBJS)		:
				$(MKDIR) $@

$(NAME)			: $(DIR_OBJS) $(OBJS)
				$(COMPIL) $(CPP_FLAGS) $(OBJS) -o $(NAME)
				echo "$(BOLD)${GREEN}$(ERASE)--> $(NAME) generated <--${END}"

$(DIR_OBJS)/%.o	: %.cpp 
				@$(MKDIR) $(dir $@)
				@$(COMPIL) $(CPP_FLAGS) -o $@ -c $< 

v				:
				@python3 TESTER_CONTAINERS42/tester.py -v

s				:
				@python3 TESTER_CONTAINERS42/tester.py -s

m				:
				@python3 TESTER_CONTAINERS42/tester.py -m

o				:
				@python3 TESTER_CONTAINERS42/tester.py -o

d				:
				@python3 TESTER_CONTAINERS42/tester.py -d

test			:
				@$(COMPIL) $(CPP_FLAGS) -g3 -fsanitize=address zmy_tests/main.cpp -Iinc -o zmy_tests/mytest; ./zmy_tests/mytest # ; rm zmy_tests/mytest
				

# Pour utiliser le debugger LLDB : compiler avec flag -g
ctest			:
				@$(COMPIL) $(CPP_FLAGS) -g zmy_tests/main.cpp -Iinc -o zmy_tests/mytest 

clean:
				${RM} $(OBJS)

fclean:			clean
				${RM} $(NAME) $(DIR_OBJS) zmy_tests/test
				echo "${RED}XXXX CLEAN XNXX${END}"

re:				fclean all

.PHONY: 		clean fclean all re 
.SILENT:		clean fclean all re $(NAME) $(DIR_OBJS)