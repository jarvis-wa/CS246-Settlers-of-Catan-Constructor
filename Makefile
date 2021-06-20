CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = dice.o exception.o player.o observer.o subject.o vertex.o tile.o edge.o board.o textdisplay.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = constructor

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
