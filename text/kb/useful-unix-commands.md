The Unix command-line snippets by chaotic order.
================================================

Boot
----
* /init
* /linuxrc
* /sbin/init
* /etc/inittab
* /etc/init.d/rcS

* 0 halt
* 1 single user
* 2-4 user defined
* 5 X11
* 6 Reboot
* Default is defined in /etc/inittab, eg: id:3:initdefault:

System
------

Users
-----
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
    ab -n 1000 -c 100 http://localhost:<port>/
    curl ifconfig.me
    sudo netstat -lntp
    sudo netstat -n --listening --program
    iftop
    iptraf

### Discovery
    nmap -sP 10.0.0.0/16 # 10.0.0.0/16 ping scan using nmap.
    avahi-browse -a

### Access
    cat /dev/dsp | ssh me@remotebox "cat > /dev/dsp"

### Optimized resolv.conf
    nameserver 8.8.8.8
    nameserver 8.8.4.4
    nameserver 4.2.2.2
    option rotate
    option timeout:1

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

### Files
    mkdir -p Maildir/{new,cur,tmp}

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
    strace
    ldd
    dmesg

lsof
----
    lsof -i      -- Show all connections with -i
    lsof -iTCP   -- Show only TCP (works the same for UDP)
    lsof -i :22  -- -i :port shows all networking related to a given port
    lsof -i@192.168.1.5  -- To show connections to a specific host, use @host
    lsof -i@192.168.1.5:22  -- Show connections based on the host and the port using @host:port
    lsof -i| grep LISTEN  -- Grepping for "LISTEN" shows what ports your system is waiting for connections on
    lsof -i| grep ESTABLISHED  -- Grepping for "ESTABLISHED" shows current active connections
    lsof -u daniel -- Show what a given user has open using -u
    lsof -c syslog-ng -- See what files and network connections a command is using with -c
    lsof /var/log/messages -- Pointing to a file shows what's interacting with that file
    lsof -p 10075 -- The -p switch lets you see what a given process ID has open, which is good for learning more about unknown processes
    lsof -t -c Mail -- The -t option returns just a PID
    lsof -a -u daniel -i @1.1.1.1 -- Using-a allows you to combine search terms, so the query below says, "show me everything running as daniel connected to 1.1.1.1"
    kill -HUP `lsof -t -c sshd` -- Using the -t and -c options together you can HUP processes
    kill -9 `lsof -t -u daniel` -- You can also use the -t with -u to kill everything a user has open
    lsof +L1 -- +L1 shows you all open files that have a link count less than 1, often indicative of a cracker trying to hide something

Netcat
------
    nc -l 8080 -- server mode on a specified port listening for incoming connections
    nc localhost 8080 -- client mode trying to connect on the port(2389) just opened
    nc -l 2389 > test, cat testfile | nc localhost 2389 -- use netcat to transfer files
    nc -4 -u -l 2389, nc -4 -u localhost 2389 -- use netcat with UDP protocol

Unsorted
--------
    rundll32 url.dll,FileProtocolHandler http://linux.org

    curl http://ajax.googleapis.com/ajax/services/language/translate\?langpair\=en\|ru\&v\=1.0\&q\=hello

    until diff <(cat /dev/urandom|strings|dd bs=1 count=$(stat -c %s hamlet.txt) 2>/dev/null) hamlet.txt;do type;done # infinity monkeys -- /via @climagic

    grep 938a03a76c531f49fa9e303578796158 <(md5sum *) # Check which files if any in current directory have provided md5sum. /via @climagic

    /usr/lib/xscreensaver/apple2 -text -fast -program $SHELL # Another one to try. Thanks @ghalfacree


From my Track
-------------
### Unix time to Local one
    date -d@1234567890
    python -c 'import time; print time.ctime(1234567890)'
    perl -e 'print scalar localtime(1234567890),"\n";'

### GCC Optimization Flags dump
    gcc -march=native -Q --help=target
    gcc -march=native -Q --help=optimizers

### Commandline Mail with an attachment
    mailx -s "This is it" someone@someplace < somefile
    uuencode file.txt file.txt | mail email@address.com

### Создание резервного образа жесткого диска
    dd if=/dev/hda | gzip > /mnt/hdb1/system_drive_backup.img.gz
### обратное действие:
    gzip -dc /mnt/hdb1/system_drive_backup.img.gz | dd of=/dev/hda
### Образ диска через SSH
    plink okertanov@crater.espectrale.com "sudo dd if=/dev/sda1 | gzip" > crater-sda1-12.05.2009.img.gz
### DD over SSH
    iPhone# dd if=/dev/rdisk0s1 bs=1M | ssh -c arcfour root@imac dd of=/tmp/102root.dd
    imac# dd if=102root.dd | ssh root@iphone dd of=/dev/rdisk0s1 bs=1M

### Заблокировать TCP порт
    sudo iptables -A OUTPUT -p TCP -d 192.168.1.101 --dport 80 -j DROP

### Выполнять комманду shell в цикле
    while : ; do ls './' ; done
    for i in {1..10}; do ./something &; done

### RSync example
    #!/bin/bash
    FROM='/Users/okertanov/Sites/www.espectrale.com/'
    TO='okertanov@crater.espectrale.com:/home/okertanov/public_html/www.espectrale.com/public'
    OPTIONS='--progress --stats --compress --recursive --times --perms --links --archive --delete'
    SHELL='--rsh=ssh'
    EXCLUDE='--exclude "*bak" --exclude "*~"'
    rsync --verbose $SHELL $OPTIONS $EXCLUDE $FROM $TO

### Close vim you left open remotely
    DISPLAY=:0 vim --servername GVIM --remote-send '<Esc>:wqa<CR>'

### Fetchmail with Imap .fetchmailrc line
    poll imap.gmail.com protocol IMAP user "username@gmail.com" there with password "password" nofetchall keep ssl

Links
-----
    http://www.mnxsolutions.com/quick-tip/how-little-you-know-and-some-useful-commands-for-the-week.html
    Основы Linux от основателя Gentoo. http://habrahabr.ru/blogs/linux/116907/
    http://wiki.fornex.com/index.php/%D0%9A%D0%BE%D0%BC%D0%B0%D0%BD%D0%B4%D1%8B_Linux
    A Sysadmin's Unixersal Translator (ROSETTA STONE) OR   What do they call that in this world? http://bhami.com/rosetta.html
