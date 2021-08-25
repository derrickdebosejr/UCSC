JAVASRC = ChessBoard.java  ChessList.java ChessPiece.java King.java Node.java Queen.java Rook.java Bishop.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = ChessBoard
CLASSES = ChessBoard.class ChessList.class ChessPiece.class King.class Node.class Queen.class Rook.class Bishop.class
JARFILE = ChessBoard.jar

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)
clean:
	rm $(CLASSES) $(JARFILE)
