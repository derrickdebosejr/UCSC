JAVASRC = SlugFest.java Node.java BankQueue.java Client.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = SlugFest
CLASSES = SlugFest.class Node.class BankQueue.class Client.class
JARFILE = SlugFest.jar

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