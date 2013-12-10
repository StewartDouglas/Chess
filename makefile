main: main.o chess.o chessboard.o position.o piece.o
	g++ -Wall -g main.o chess.o chessboard.o position.o piece.o -o main

main.o: ChessMain.cpp ChessMain.h chess.h piece.h chessboard.h position.h
	g++ -Wall -g -c ChessMain.cpp -o main.o

chess.o: chess.cpp chess.h
	g++ -Wall -g -c chess.cpp -o chess.o

piece.o: piece.cpp piece.h chessboard.h position.h chess.h
	g++ -Wall -g -c piece.cpp -o piece.o

position.o: position.cpp position.h chess.h 
	g++ -Wall -g -c position.cpp -o position.o

chessboard.o: chessboard.cpp chessboard.h position.h piece.h chess.h
	g++ -Wall -g -c chessboard.cpp -o chessboard.o

clean:
	rm -f *.o
