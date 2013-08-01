
ISO_IMAGES=$(wildcard *.iso)

all: md5

md5:
	-@echo Running for: $(ISO_IMAGES)
	-@echo
	-@$(foreach file,$(ISO_IMAGES), if [ -e $(file) ]; then cat $(file).md5 && md5sum -c $(file).md5 ; fi; )
	-@echo

.PHONY: all md5 clean

.SILENT: clean

