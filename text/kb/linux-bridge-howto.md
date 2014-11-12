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

Management console
------------------

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

