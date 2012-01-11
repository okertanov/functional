
all:
	

install:
	

deb:
	debuild --lintian --check-dirname-level 0 -us -uc -I.git

debclean:
	-@debuild clean 2>&1 > /dev/null

clean:
	-@rm -rf debian/etc-immunity
	-@rm -f  debian/etc-immunity.debhelper.log debian/etc-immunity.substvars
	-@rm -f  debian/files debian/md5sums
	-@rm -f  debian/*.debhelper

.PHONY: all install deb debclean clean

.SILENT: clean

