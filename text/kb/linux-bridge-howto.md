How to setup Linux bridge
=========================

The problem
-----------
Lattelecom delivers new Alcatel-Lucent GPON modems but actually it is a router.

Hardware and OS
---------------
### Alcatel-Lucent I-240W-A

### BroadLight Alto BL23570 GPON
For VoIP offering 500 MHz speed, 5x Gigabit Ethernet, 2x PCIe and 2x USB ports, and 800 MHz processor in a 16x16 mm LFBGA-289 package.
MIPS32 74K Core

### OS
BROADLIGHT Lilac Linux (FS version 2.0.85.2, issue 2011-07-17-232953-juno
Linux 192.168.0.0 2.6.34.8-BCM2.1.11.0 #1 Mon Aug 4 21:00:18 CST 2014 mips GNU/Linux
Linux version 2.6.34.8-BCM2.1.11.0 (buildmgr@AONT10) (gcc version 4.4.1 (Wind River Linux Sourcery G++ 4.4a-323) ) #1 Mon Aug 4 21:00:18 CST 2014

#### /proc/cmdline:
ubi.mtd=1 root=ubi0_0 rw rootfstype=ubifs ip=192.168.0.0:192.168.1.22:192.168.2.55:255.255.255.0:::off console=ttyS0,115200 bootversion=Aug-04-2014--20:58:01

#### /proc/cpuinfo
system type     : Broadlight Lilac SOC
processor       : 0
cpu model       : MIPS 74Kc V4.12
BogoMIPS        : 248.21
wait instruction    : yes
microsecond timers  : yes
tlb_entries     : 64
extra interrupt vector  : yes
hardware watchpoint : yes, count: 4, address/irw mask: [0x0000, 0x0000, 0x0000, 0x0000]
ASEs implemented    : mips16 dsp
shadow register sets    : 1

#### Mounts
rootfs on / type rootfs (rw)
ubi0_0 on / type ubifs (rw,relatime)
proc on /proc type proc (rw,relatime)
sysfs on /sys type sysfs (rw,relatime)
devpts on /dev/pts type devpts (rw,relatime,gid=5,mode=620)
tmpfs on /dev/shm type tmpfs (rw,relatime)
/dev/ram1 on /tmp type tmpfs (rw,relatime,size=65536k)
/dev/ubi1_1 on /configs type ubifs (rw,relatime)
/dev/ubi5_0 on /logs type ubifs (rw,relatime)

#### 

#### net.conf
ip=78.84.147.76
gateway=78.84.128.1
mask=255.255.224.0

#### Ifconfig
br0       Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70
          inet addr:192.168.1.254  Bcast:192.168.1.255  Mask:255.255.255.0

brsfu     Link encap:Ethernet  HWaddr 54:A6:19:9B:54:71

eth0      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

eth1      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

eth2      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

eth3      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

gpon0     Link encap:Ethernet  HWaddr 02:4C:FA:D5:DD:11
          inet addr:192.168.2.2  Bcast:192.168.2.255  Mask:255.255.255.0

lo        Link encap:Local Loopback

wan0      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:74

wan0.2323 Link encap:Ethernet  HWaddr 54:A6:19:9B:54:74
          inet addr:78.84.147.76  Bcast:78.84.159.255  Mask:255.255.224.0

wan1      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:75

wan2      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:76

wan3      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:77

wan4      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:78

wan4.3    Link encap:Ethernet  HWaddr 54:A6:19:9B:54:78

wan5      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:79

wan5.5    Link encap:Ethernet  HWaddr 54:A6:19:9B:54:79
          inet addr:10.74.192.129  Bcast:10.74.223.255  Mask:255.255.224.0

wan6      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:7A

wan7      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:7B

wan8      Link encap:Ethernet  HWaddr 54:A6:19:9B:54:71

wifi_fp0  Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

wifi_fp1  Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

wifi_fp2  Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

wifi_fp3  Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

wlan0     Link encap:Ethernet  HWaddr 54:A6:19:9B:54:70

Management console
------------------
### Users
adminadmin
Tdvdran:dsls
AdminGPON:dsls

### Webs/HTML
application        head.html          login_main.html    management         reg.html           security           unauthorized.html
diagnose           login.html         main.html          network            reg2.html          status

Problems
--------
### NMap outside
PORT      STATE SERVICE
1234/tcp  open  hotline
8080/tcp  open  http-proxy
49158/tcp open  unknown

## NMap inside
PORT      STATE SERVICE
22/tcp    open  ssh
23/tcp    open  telnet
80/tcp    open  http
1234/tcp  open  hotline
49158/tcp open  unknown

The process
-----------

Links
-----
### Bridge
[Ubuntu community: Network Connection Bridge](https://help.ubuntu.com/community/NetworkConnectionBridge)  
[How to configure a Linux bridge interface](http://xmodulo.com/how-to-configure-linux-bridge-interface.html)  
[Kernel Korner - Linux as an Ethernet Bridge](http://www.linuxjournal.com/article/8172)  
[Ethernet-Bridge-netfilter-HOWTO: Setting up the bridge](http://www.tldp.org/HOWTO/Ethernet-Bridge-netfilter-HOWTO-3.html)  
[Linux Foundation](http://www.linuxfoundation.org/collaborate/workgroups/networking/bridge)  
[xgu.ru: Linux Bridge](http://xgu.ru/wiki/Linux_Bridge)  
[Pseudo-bridges with Proxy-ARP](http://lartc.org/howto/lartc.bridging.proxy-arp.html)  
### Other
[Lattelecom IPTV Manual ru](http://lattelecom.lv/images/Majai/Komplekti/PDF/Interaktiva-TV-lietotaja-rokasgramat_RU.pdf)  

