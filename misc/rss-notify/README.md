RSS notify project
==================

Ubuntu
------
cvs subversion mc vim-full ssh build-essential autoconf automake libtool
libcurl4-openssl-dev  libcurl-dev  libxml2-dev libnxml0-dev
libnotify-bin

Build
-----
cvs -d:pserver:anonymous@ippolita.net:/home/cvs login
cvs -z3 -d:pserver:anonymous@ippolita.net:/home/cvs co libmrss
cd libmrss
cvs update -dP
./autogen.sh
./configure --prefix=/home/okertanov/projects/rss-notify/libmrss/
make
make install

Locales Test
------------
sudo vim /var/lib/locales/supported.d/ru
sudo dpkg-reconfigure locales
sh -c "export LANG=ru\_RU.CP1251; gnome-terminal --disable-factory"

Links
-----
    http://www.vanheusden.com/rsstail/
    http://www.autistici.org/bakunin/libmrss/doc/

    http://www.opengroup.org/onlinepubs/009695399/functions/localtime.html
    http://www.uwm.edu/cgi-bin/IMT/wwwman?topic=timezone(3)&msection=

