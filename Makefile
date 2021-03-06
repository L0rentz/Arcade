##
## EPITECH PROJECT, 2021
## G-JAM-001-NCE-0-2-jam-marton.szuts
## File description:
## Makefile
##

NAME			=	arcade

CXX				=	g++

DIR1			=	./GraphicalLibs/Interface/
DIR2			=	./Core/
DIR3			=	./Games/Interface/
DIR4			=	./Utils/

CALL_MAKE_PACMAN	=	cd Games/Pacman && make
CALL_MAKE_SNAKE		=	cd Games/Snake && make
CALL_MAKE_MENU		=	cd Games/Menu && make
CALL_MAKE_SDL		=	cd GraphicalLibs/Sources/SDL && make
CALL_MAKE_SFML		=	cd GraphicalLibs/Sources/SFML && make
CALL_MAKE_NCURSES	=	cd GraphicalLibs/Sources/Ncurses && make

INC				=	$(DIR1) $(DIR2) $(DIR3) $(DIR4)
INC_PARAMS		=	$(foreach d, $(INC), -I$d)

CXXFLAGS		=	-Wall -Wextra $(INC_PARAMS) -ldl

SRC				=	./Core/main.cpp \
					./Core/DL.cpp \
					./Core/Core.cpp \

OBJ				=	$(SRC:.cpp=.o)

RM				=	rm -rf

all: $(NAME)

core: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

games:
	$(CALL_MAKE_PACMAN)
	$(CALL_MAKE_SNAKE)
	$(CALL_MAKE_MENU)

graphicals:
	$(CALL_MAKE_SDL)
	$(CALL_MAKE_SFML)
	$(CALL_MAKE_NCURSES)

$(NAME): $(OBJ)
	$(CALL_MAKE_MENU)
	$(CALL_MAKE_PACMAN)
	$(CALL_MAKE_SNAKE)
	$(CALL_MAKE_SDL)
	$(CALL_MAKE_SFML)
	$(CALL_MAKE_NCURSES)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)
	cd Games/Pacman && make clean
	cd Games/Snake && make clean
	cd Games/Menu && make clean
	cd GraphicalLibs/Sources/SDL && make clean
	cd GraphicalLibs/Sources/SFML && make clean
	cd GraphicalLibs/Sources/Ncurses && make clean

fclean: clean
	$(RM) $(NAME)
	cd Games/Pacman && make fclean
	cd Games/Snake && make fclean
	cd Games/Menu && make fclean
	cd GraphicalLibs/Sources/SDL && make fclean
	cd GraphicalLibs/Sources/SFML && make fclean
	cd GraphicalLibs/Sources/Ncurses && make fclean

re: fclean all

.PHONY: all clean fclean re