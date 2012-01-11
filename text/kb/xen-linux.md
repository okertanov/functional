XEN on Ubuntu, Ubuntu on XEN
============================

Task
----
    [x] zion.lan dom0 infrastructure
        [x] Ubuntu linux 11.10 AMD64
        [-] RAID1
        [x] partitioning and lvm
            [x] host boot partition
                    /dev/sda1 + _/dev/sdb1_ ->
                    _/dev/md1_ - 2GB ext4
            [x] lvm vg
                    /dev/sda52 + _/dev/sdb5_ ->
                    _/dev/md2_ - rest space -> zion_vg
            [x] host root lvm lv
                    zion_zion_vg -> dom0-zion-root - 32GB ext4
            [x] host swap lvm lv
                    zion_vg -> dom0-zion-swap - 8GB swap/etc/sudoers: syntax error
            [x] domU lvm root/swap lv's
                    zion_vg -> domu-hostname-root - 24GB,
                    zion_vg -> domu-hostname-swap - 4GB
            [x] verbose volume labels for all
        [x] host network
            [x] hostname:zion.lan,
            [x] ip:192.168.1.XY, mask:255.255.255.0, gw:192.168.1.1, ns:192.168.1.1
            [x] master firewall & dhcp settings
            [x] sudo vim /etc/hostname /etc/hosts /etc/resolv.conf
            [x] sudo vim /etc/network/interfaces
            [x] sudo ethtool eth0
        [x] bridged subnet
                    [x] hosts: zion.xlan, helsinki.xlan...
                    [ ] dns
                    [ ] dhcp
                    [x] bridge: xenbr0
                    [ ] subnet:192.168.21.0/24,
                    [ ] gw:192.168.21.1,
                    [ ] domu:192.168.21.2,
                    [ ] 192.168.21.3...
        [x] routing, nat & bridge
                    sudo vim /etc/sysctl.conf
                        net.ipv4.ip_forward=1
                        net.ipv4.conf.all.proxy_arp=1
                    sudo sysctl -p
                    sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
        [ ] security, firewall
                    [x] sudo ufw enable
        [ ] users
            [x] PV root
            [x] mradmin
                    Mobile Rack Administrator <mradmin@zion.lan>
            [x] mrtester
                    Mobile Rack Tester <mrtester@zion.lan>
            [x] sudo vim /etc/sudoers /etc/sudoers.d/mradmin
        [x] ssh, ssh keys
        [x] XEN hypervisor & kernel
        [ ] XEN client applications: console, xen client, api, web
        [ ] XEN System configuration & config review
        [x] XEN VNC
        [ ] NTP
        [ ] LDAP
                    sudo aptitude install slapd ldap-utils
        [ ] Host DNS
                    sudo vim /etc/resolv.conf
        [x] maintenance
            [x] /etc under the git control
            [ ] monitoring
                    sudo aptitude install monit
        [ ] backups
            [ ] initial working configuration
            [ ] incremental working configuration
            [ ] continuous
    [ ] domU nodes
        [x] zion.xlan
            [x] Ubuntu linux 11.10 amd64
            [x] config
                    /etc/xen, /srv/xen/config
            [x] domains
                    sudo mkdir /srv/xen/domains
            [ ] templates (/srv/xen/templates)
        [x] tallinn.xlan PV
            [x] ubuntu linux 10.04 amd64
            [-] Android SDK/Emulator
            [-] Firefox, Chrome, Opera
            [x] ssh
            [?] vnc
        [ ] helsinki.xlan PV
            [ ] ubuntu linux 11.10 amd64
            [ ] Android SDK/Emulator
            [ ] Firefox, Chrome, Opera
            [ ] ssh
            [ ] vnc
        [x] redmond.xlan HVM
            [x] Windows XP i386
            [ ] paravirtualized drivers
            [ ] IE 7, 8, 9 browser pack
            [x] Firefox, Chrome, Opera
            [x] WinMobile 6.5
            [ ] BBry Simulator
            [ ] rdp
            [x] vnc
        [ ] seattle.xlan (vienna.xlan) HVM
            [x] Windows 7 i386
            [ ] IE 8, 9 browser pack
            [ ] WindowsPhone 7 Simulator
            [ ] Series60 Simulator
        [ ] cupertino.xlan HVM
            [ ] SL 10.7 Lion DVD image
            [ ] Xcode & iOS Simulator
            [ ] ssh
            [ ] vnc

XEN
---
### Terminology
* XEN  -- Xen is a robust, secure, high performance baremetal hypervisor
* VMM  -- Virtual machine monitor
* PV   -- Paravirtualized virtual machine
* HVM  -- Hardware virtual machine
* Dom0 -- A special privileged virtual machine that Xen hypervisor always loads on host startup
* DomU -- Xen guests
* SR   -- Storage repository (hdd, nfs, iscsi)
* VDI  -- Virtual disk image
* VBD  -- Virtual block device
* VIF  -- Virtual interface
* PIF  -- Physical interface
* EVMS -- Enterprise Volume Management System

### Hypervisor's core
* dom0 kernel
* xapi
* blktap, xenstored, consoled
* open vswitch
* squeezed
* stunnel
* xsconsole
* xe

### Detect
    dmidecode
    /proc/xen
    /proc/xen/capabilities
    /sys/hypervisor

Prerequisites
-------------
### VT-X
    grep -i vmx /proc/cpuinfo

### XEN dom0
    uname -a
    dmesg | grep -i xen
    grep -i xen /boot/config-2.6.XXX-YYY
    cat /proc/xen/capabilities
    sudo xm info
    sudo xm list
    sudo xm dmesg
    sudo xm dmesg | grep VMX
    sudo xm info | grep caps

Installation
-------------
    sudo aptitude search xen
    sudo aptitude install ubuntu-xen-server
    sudo aptitude install bridge-utils
    sudo aptitude install ubuntu-xen-desktop
    sudo aptitude install xenman
    sudo aptitude install xen-hypervisor
    sudo aptitude install xen-linux-system-2.6.XXX-xen-amd64
    sudo aptitude install xen-utils
    sudo aptitude install xen-tools
    sudo aptitude install xenstore-utils
    sudo aptitude install xenwatch
    sudo aptitude install xen-shell

MDADM RAID1
-----------

LVM
---
### Terminology
* PV -- Physical volume
* VG -- Volume group
* LV -- Logical volume
* PE -- Physical extent
* LE -- Logical extent
* FS -- Filesystem

### Topology
    sda1     sda2     sdb     sdc    -- PV
     |        |        |       |
     |        |        |       |
     +--------+- VG00 -+-------+     -- VG
                  |
     +-------+-------+---------+
     |       |       |         |
    root    usr     home      var    -- LV
     |       |       |         |
    ext3  reiserfs reiserfs   xfs    -- FS

### LVM Initialization
    sudo aptitude install lvm2
    sudo aptitude install system-config-lvm
    sudo modprobe dm_mod modprobe dm_mirror modprobe dm_snapshot
    sudo pvcreate /dev/sda5
    sudo vgcreate zion_vg /dev/sda5
    sudo lvcreate -n myguest-disk -L +100G zion_vg # To create a volume
    sudo lvcreate -n myguest-swap -L +4G   zion_vg # To create another volume
    sudo pvdisplay
    sudo vgdisplay
    sudo lvdisplay -C
    sudo lvdisplay
    sudo lvscan
    sudo lvs

### LLVM Backup
    lvcreate -L10G -s -n hdd-backup /dev/vg/hdd-online
    dd if=/dev/vg/hdd-backup bs=1024000 | gzip -cf > /mnt/backups/hdd-online-snapshot.gz
    lvremove /dev/vg/hdd-backup

### LLVM Restore
    gunzip -c /mnt/backups/hdd-online-snapshot.gz | dd of=/dev/vg/hdd-online bs=1024000

### Another LVM story
    pvcreate /dev/sda3
    pvcreate /dev/sdb2
    vgcreate main-vol /dev/sda3 /dev/sdb2
    vgscan
    lvcreate -n zachome --size 50g main-vol
    lvcreate -n zachomeswp --size 1g main-vol
    mkfs.ext3 /dev/main-vol/zachome
    mkswap /dev/main-vol/zachomeswp
    resize2fs /dev/main-vol/zachome 40000
    lvreduce -L-10g /dev/main-vol/zachome   #subtract 10Gb from current size!
    pvscan
    lvscan

Or Loop
-------
    sudo modprobe loop max_loop=255
    sudo vim /etc/modules => loop max_loop=64
    sudo dd if=/dev/zero of=/mnt/domains/myslice/disk.img bs=1 count=0 seek=25G
    sudo dd if=/dev/zero of=/mnt/domains/myslice/swap.img bs=1G count=1
    sudo mkfs.ext3 ./disk.img
    sudo mkswap ./swap.img

Configuration
-------------
    sudo vim /etc/xen/xend-config.sxp
    sudo vim /etc/xen-tools/xen-tools.conf
    sudo vim /etc/xen-tools/skel
    sudo vim /etc/xen-tools/role.d
    sudo ls -l /etc/xen/auto
    sudo /etc/init.d/xend restart

Networking for DomU
-------------------
### Static
    auto lo
    iface lo inet loopback

    auto eth0
    iface eth0 inet static
    address 192.168.44.247
    netmask 255.255.252.0
    gateway 192.168.47.254
### DHCP
    auto lo
    iface lo inet loopback

    auto eth0
    iface eth0 inet dhcp
### hostname
    vim /etc/hostname
    127.0.0.1       localhost
    127.0.1.1       yourhostname

Running
-------
    sudo xen-create-image --hostname=xen1.example.com --role=gdm|minimal
    sudo vim /etc/xen/xen1.example.com.cfg
    sudo xm create -c /etc/xen/xen1.example.com.cfg
    sudo xm list
    sudo xm console
    sudo xentop
    sudo xm shutdown xen1.example.com

Bootstrapping sample
--------------------
    sudo mkdir -p /srv/xen/config && sudo ln -s /srv/xen/config /etc/xen/config # /etc/xen/HOSTNAME.cfg
    sudo mkdir -p /srv/xen/domains && cd /srv/xen/domains # /srv/xen/domains/HOSTNAME
    lvcreate -L10G -n example.domain.com VolumeGroup
    wget http://ca.archive.ubuntu.com/ubuntu/dists/natty/main/installer-amd64/current/images/netboot/xen/xm-debian.cfg
    wget http://ca.archive.ubuntu.com/ubuntu/dists/natty/main/installer-amd64/current/images/netboot/xen/initrd.gz
    wget http://ca.archive.ubuntu.com/ubuntu/dists/natty/main/installer-amd64/current/images/netboot/xen/vmlinuz
    vim xm-debian.cfg
    xm create -f xm-debian.cfg -c install=true install-kernel="vmlinuz" install-ramdisk="initrd.gz" \
                install-mirror="http://ca.archive.ubuntu.com/ubuntu" install-arch=amd64 install-method=network
    ... install
    modprobe xen-blkfront && exit
    echo "xen-blkfront" >> /etc/initramfs-tools/modules
    update-initramfs -u

XEN Flavors
-----------
* Xensource XEN
* Citrix XenServer / XenCenter / XenClient
* Xen Cloud Platform (XCP)
* Xen Client Initiative (XCI)

OSX on XEN
----------
    ...Disk Util to dump retail osx10.6 dvd -> Mac OS 10.6 X Install DVD.cdr
    ...Disk Util to create empty DVD image: guid partition, osx jurnalled, extended -> OSX106x86Image.dmg
    sudo asr imagescan --source OSX106x86Image.dmg --filechecksum
    sudo asr -noverify -source /Volumes/Mac\ OS\ X\ Install\ DVD -target /Volumes/OSX106x86Image
    diskutil list
    cd Chameleon-2.0-RC4-r684-bin/i386
    sudo fdisk -f boot0 -u -y /dev/rdisk2
    sudo dd if=boot1h of=/dev/rdisk2s2
    sudo cp Bootloader/Bootloader.pkg/Contents/Resources/boot/boot /Volumes/OSX106x86Image
    sudo mv Extra /Volumes/OSX106x86Image
    ...Disk Util to convert .dmg to .cdr(iso)

Links
=====
* [help.ubuntu.com/community/Xen](https://help.ubuntu.com/community/Xen)
* [man xen-create-image](http://man.cx/xen-create-image%288%29)
* [Xen server своими руками. Часть вторая.](http://habrahabr.ru/blogs/sysadm/50121/)
* [Пошаговое руководство по установке Debian 5.0 Lenny + XEN + LVM + Routing](http://habrahabr.ru/blogs/hosting/83656/)
* [Руководство пользователя Xen v3.0](http://xgu.ru/xen/manual/)
* [Xen Cloud Platform в условиях предприятия](http://habrahabr.ru/blogs/virtualization/104025/)
* [Ubuntu Natty Narwhal and Xen](http://www.mmacleod.ca/blog/2011/05/ubuntu-natty-narwhal-and-xen/)
* [wiki.xensource.com/xenwiki/XenFaq](http://wiki.xensource.com/xenwiki/XenFaq)
* [wiki.xensource.com/xenwiki/XenDemoLaptop](http://wiki.xensource.com/xenwiki/XenDemoLaptop)
* [Xen Common Problems](http://wiki.xensource.com/xenwiki/XenCommonProblems)
* [Xen Management Tools](http://wiki.xensource.com/xenwiki/XenManagementTools)
* [community.citrix.com XenCenter](http://community.citrix.com/display/xs/XenCenter)
* [wiki.debian.org/Xen](http://wiki.debian.org/Xen)
* [Повесть о Linux и LVM](http://xgu.ru/wiki/LVM)
* [Snow Leopard Server on Xen](http://wiki.osx86project.org/wiki/index.php/Snow_Leopard_Server_on_Xen)
* [Snow Leopard as guest on a Xen DomU](http://www.bisente.com/blog/2011/03/15/macos-xen-snow-leopard-as-guest-on-a-xen-domu/)
* [Linux, Mac OS X и Windows - вместе! ](http://blogs.mail.ru/mail/vanderpool/76BA55E357348565.html)
* [Ubuntu UFW](https://help.ubuntu.com/community/UFW)
* [Ubuntu Codenames](https://wiki.ubuntu.com/DevelopmentCodeNames)
* [CentOS LVM Administrator's Guide](http://www.centos.org/docs/5/html/Cluster_Logical_Volume_Manager/)

