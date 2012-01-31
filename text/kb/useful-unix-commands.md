The Unix command-line snippets by chaotic order.
================================================

System
------

Users
-----
    useradd - TBD
    usermod -a -G developers user

Environment
-----------
### Status
    env
    printenv
    export -n LC_ALL
###Persistent environment variables
    ~/.profile
    ~/.bash_profile
    ~/.bashrc
    /etc/environment
    /etc/profile
    /etc/bash.bashrc
### Application variables
    $USER
    $HOME
    $PWD
    $SHELL
    $TZ
    $TERM
    $COLUMNS
    $LINES
    $EDITOR
    $DISPLAY
    $LD_PRELOAD
### Software development variables
    $CC
    $CFLAGS
    $CXXFLAGS
    $CPPFLAGS
    $LIBRARY_PATH
    $INCLUDE

Filesystem
----------

Network
-------
### Config files
    /etc/host.aliases
### Monitoring
    mtr www.google.com
    ab http://google.com/
    curl ifconfig.me
    sudo netstat -lntp
    sudo netstat -n --listening --program
    iftop

### Discovery
    nmap -sP 10.0.0.0/16 # 10.0.0.0/16 ping scan using nmap.
    avahi-browse -a

### Access
    cat /dev/dsp | ssh me@remotebox "cat > /dev/dsp"

Services control
----------------
    sudo service --status-all
    sudo initctl list

Posix Shell
-----------
### Keys
    Ctrl A
    Ctrl E
    Alt  .
    Ctrl X Ctrl E

### Commandline
    \ls
    sudo !!
    cp -p mydomain.com.{au,cn}.zone # Brace expansion
    ls -l {/usr,}{/local,}/{s,}bin/? # Check all common bin and sbin directories
    diff app{-dev,-prod}/some/dir/twice.txt
    diff <(grep = config.txt) <(grep = config.txt-new) # Compare just the assignment lines of two config files

### Cycles
    for i in {1..10}; do ./something &; done
    for i in {0001..0100} ; do wget http://www.someurl .com/images/IMG_${i}.JPG ; done

### Ranges
    echo {1..10}
    touch /tmp/{a,b,c}

### Find, grep
    find ./* -maxdepth 1 -prune -type d -print0 | xargs -0 -Ii ls -d i
    find ./  -maxdepth 2 -name .git -print | while read repo; do cd $(dirname $repo); git pull; done

    find $HOME -iname '*' -type f -size +100M
    find . \( -name '*.mp3' -o -name '*.jpg' \) -name 'foo*' -print
    find /usr -perm -4000 -print

    find source \( -name CVS -prune \) -o \( -type f -print \)

### Unix time
    date -d@1234567890
    or
    perl -e 'print scalar localtime(1234567890),"\n";'

### Debian, Ubuntu
    sudo add-apt-repository ppa:<repository-name>
    apt-cache policy package
    dpkg-deb -x package.deb ~/projects/package-decompressed

    dpkg -i package-ver.deb
    dpkg -l
    dpkg -l <search_term>
    dpkg -L <package>
    dpkg -c <package>
    dpkg -S /path/to/file
    dpkg -p <package>

Applications
------------
    sudo update-alternatives --config editor

Kernel
------
    dmidecode
    lspci
    lsusb
    lsof
    strace
    ltrace

Performnance
------
    sudo aptitude install linux-tools-common

    http://www.pixelbeat.org/programming/profiling/
    perf record -a -g sleep 10
    perf report --sort comm,dso

Tops
----
* top
* atop
* htop
* iotop
* iftop
* powertop
* itop
* kerneltop
* jnettop
* sntop
* latencytop
* xrestop
* slabtop
* apachetop
* sqtop
* pg\_top
* mytop
* xentop
* virt-top
* nload
* nethogs
* iptstate
* trafshow
* iptraf
* tload

Data backup/restore
-------------------
### Via NC
    Backup:
    1) nc -l -p 9000 | gzip -1 -c > ./sda.img.gz
    2) dd if=/dev/sda | nc -w 5 192.168.1.101 9000

    Restore:
    1) zcat ./sda.img.gz | nc 192.168.1.102 9000
    2) nc -l -p 9000 | dd of=/dev/sda

### Via Plink
    plink okertanov@example.com "sudo dd if=/dev/sda1 | gzip" > example-sda1-12.05.2011.img.gz

### DD over SSH
    Backup:
    iPhone# dd if=/dev/rdisk0s1 bs=1M | ssh -c arcfour root@imac dd of=/tmp/102root.dd

    Restore:
    imac# dd if=102root.dd | ssh root@iphone dd of=/dev/rdisk0s1 bs=1M

Logs
----
    tail -f /var/log/messages
    watch -d ps

Development
-----------
    autogen.sh (a.k.a. buildconf) provides automatic build system preparation
    strings file.elf- show binary file strings
    ltrace - a library call tracer
    strace - a system calls runtime monitor
    objdump - displays information about object files

Debug
-----
    strace
    ldd
    dmesg
    lsof

Testing
-------
    ab -r30000 -c100 http://localhost:<port>/  -- Apache Bench

Unsorted
--------
> rundll32 url.dll,FileProtocolHandler http://linux.org
>
> ``GET "http://www.google.com/dictionary?langpair=en|ru&q=work&hl=ru&aq=f" | grep dct-tt | sed /'class=\"dct-e/d' | sed '/<a\ href/d' | sed 's/<span class="dct-tt">//g' |sed 's/<\/span>//' | sed '/<span /d' | head -n 3d 's/``
>
> curl http://ajax.googleapis.com/ajax/services/language/translate\?langpair\=en\|ru\&v\=1.0\&q\=hello

Links
-----
    http://www.mnxsolutions.com/quick-tip/how-little-you-know-and-some-useful-commands-for-the-week.html
    Основы Linux от основателя Gentoo. http://habrahabr.ru/blogs/linux/116907/
    http://wiki.fornex.com/index.php/%D0%9A%D0%BE%D0%BC%D0%B0%D0%BD%D0%B4%D1%8B_Linux
    A Sysadmin's Unixersal Translator (ROSETTA STONE) OR   What do they call that in this world? http://bhami.com/rosetta.html