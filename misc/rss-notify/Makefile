VERSION=1.5

DEBUG=-g
#LDFLAGS=-lmrss $(DEBUG) -L../libmrss/lib
LDFLAGS=-lcurl ../libmrss/lib/libmrss.a /usr/lib/libnxml.a
CFLAGS=-O2 -Wall -DGNU_SOURCE -D_XOPEN_SOURCE=500 -D_FORTIFY_SOURCE -DVERSION=\"$(VERSION)\" $(DEBUG) -I../libmrss/include

DESTDIR=/home/okertanov/bin

OBJS=r2t.o

all: rsstail

rsstail: $(OBJS)
	$(CC) -Wall -W $(OBJS) $(LDFLAGS) -o rsstail

install: rsstail
	cp rsstail $(DESTDIR)/
	cp rss-notify.sh $(DESTDIR)/
#	cp rsstail.1 $(DESTDIR)/usr/share/man/man1/

clean:
	rm -f $(OBJS) core rsstail

package: clean
	# source package
	rm -rf rsstail-$(VERSION)*
	mkdir rsstail-$(VERSION)
	cp *.c *.1 Makefile* readme.txt license.* rsstail-$(VERSION)
	tar cf - rsstail-$(VERSION) | gzip -9 > rsstail-$(VERSION).tgz
	rm -rf rsstail-$(VERSION)
