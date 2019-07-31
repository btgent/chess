CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = program
OBJECTS = main.o board.o piece.o pawn.o knight.o bishop.o rook.o queen.o king.o coord.o pastmove.o futuremove.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY : clean

clean :
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
