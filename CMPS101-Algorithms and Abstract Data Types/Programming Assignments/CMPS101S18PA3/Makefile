JAVASRC = FindAnagrams.java Anagram.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = FindAnagrams
CLASSES = FindAnagrams.class Anagram.class 
JARFILE = FindAnagrams.jar

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
