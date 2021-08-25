JAVASRC = Vector.java VectorTest.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = VectorTest
CLASSES = VectorTest.class Vector.class 
JARFILE = VectorTest.jar

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