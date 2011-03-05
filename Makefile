
all: cc-gen-a

cc-gen-a.c: cc-gen-a.ss
	chicken $? 

cc-gen-a: cc-gen-a.c
	gcc $? -o $@ -lchicken

clean:
	-@echo cleaning...
	-@rm -f *.c *.o cc-gen-a 2>/dev/null

.SILENT: clean
.PHONY:  all


