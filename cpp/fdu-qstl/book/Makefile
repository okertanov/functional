TEXTEXT=qstl-book
LATEXOP=-halt-on-error -c-style-errors

all: tex pdf 

tex: $(TEXTEXT).tex
	latex $(LATEXOP) $(TEXTEXT).tex
	latex $(LATEXOP) $(TEXTEXT).tex

pdf: tex
	dvipdfm $(TEXTEXT).dvi

xls:
	echo "Fix it please, i need it!"
	echo "Starting..."

xml: $(TEXTEXT).tex
	.\exporter\parser.pl $< qstl.xml .\exporter\template.xml

clean:
	-@rm -f *.log *.toc *.dvi *.aux *.out *.pdf *.xml *.xul 


