JAVASRC = PA1.java apint.java aprat.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = PA1
CLASSES = PA1.class apint.class aprat.class 
JARFILE = PA1.jar

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
