ARM headless server (Viridis microserver) confs
---



**Here I specify and explain how to:**

A. Access to the headless Viridis ARM microserver's shell
B. Get internet access in the server (via access pc)


> content summary: 
>
>    i) configure DHCP in access machine;  
>    ii) open and configure serial link with server;  
>    iii) access server via ssh; 
>    iv) configure DNS forwarding;  
>    v) access internet in the server.


My configuration:

    ----------               ----------
    | SERVER |---------------|   PC   |-----|internet
    ----------               ----------
            eth           eth0        wlan0
        192.168.0.x    192.168.0.1  xxx.xxx.xxx.xxx


Since the ARM server available in the dpt. is a headless server (ask for login credentials and check more info about the server [here][1]), we'll have to access to it via serial-com and manage it with IPMI and/or PXE protocols (check box)


> **IPMI** (Intelligent Platform Management Interface) is a standarized message-based, hardware-level and OS independent computer
> sys interface. It is used to access and configure computers via serial
> port and can work in different scenarios, such as i) before OS is
> installed; ii) when computer is turned off; iii) after OS or sys
> failure. [more][2]

> **PXE** (Pre-boot execution environment) is an environment to boot computers using network interface, independently of data storage or
> OS. The protocol is a rough mix of DHCP protocol (to locate boot
> server/s) and TFTP (to download the initial bootstrap program and
> initial files). [more] [3]

Some tools that might be interesting (not mandatory) to install:

> **ipmitool** IPMItool provides a simple command-line interface to
> IPMI-enabled devices through an IPMIv1.5 or IPMIv2.0 LAN interface or
> Linux/Solaris kernel driver.
> 
> **cxmanage** provides a way for client code to access a Calxeda System
> on a Chip (SoC). The Cxmanage Python API focuses on the connectivity
> between the issuing client and the Baseboard Management Controller
> (BMC) by using a Python IPMI interface.
> 
> See how to install these tools [here][4]

*Note: I realized by the end of the deployment that dnsmasq is more powerfull that I thought. It may be possible to use it to configure both DHCP server and DNS forwarding capabilities in the access machine.*

###A. Access to ARM server's shell

1) Configure DHCP server
configure interfaces (static ip for DHCP server) 

edit /ect/network/interfaces:

> auto lo iface lo inet loopback
> 
> iface eth0 inet static
>     address 192.168.1.1
>     network 192.168.1.0/16
>     netmask 255.255.0.0
>     broadcast 192.168.255.255 auto eth0

 and then, to restart the service:
 

> sudo /etc/init.d/networking restart

 


2) install isc-dhcp-server

> get apt-get install isc-dhcp-server

3) configure DHCP server
edit /etc/dhct/dhctp.conf (as explained [here][5])

    ddns-update-style interim;
     
    allow booting;
    allow bootp;
     
    ignore client-updates;
    set vendorclass = option vendor-class-identifier;
     
    subnet 192.168.0.0 netmask 255.255.0.0 {
         option routers             192.168.0.1;
         option domain-name-servers 192.168.0.1;
         option subnet-mask         255.255.0.0;
         range dynamic-bootp        192.168.0.10 192.168.0.250;
         filename                   "/pxelinux.0";
         default-lease-time         604800;
         max-lease-time             604800;
         next-server                192.168.0.2;
    }

 
4) restart DHCP server

> sudo service isc-dhcp-server restart

5) open a serial communication with the server

> sudo gtkterm </dev/serial-endpoint> 115200

in case a USB-to-serial is used, the serial-endpoint is (most likely) '/dev/ttyUSB0'


6) check node addrs and figure out the one that has ssh running
this can be done in different ways. the best is to use wireshark to understand the ip range of the nodes. the cxmanage and ipmitool can be used as well.
once the range is known, use the nmap (sudo nmap -sO 192.168.0.1-28) to check in which ip we can connect via ssh to the server.

Note: it helps to check wireshark right after the serial-com connection is done. The newly assigned ip address is most likely the one who has the server's ssh endpoint.

7) connect via ssh

> ssh user@ip

 (ip gathered in the above steps)

where (in the current ARM installation)
user: ubuntu
pass: ubuntu


###B. Internet access in the server

1) Configure laptop as DHCP server, serving eth0 (as configured above)
2) Activate IP forwarding:

> \# sysctl -w net.ipv4.ip_forward=1

(forwarding everything from wlan0):

> \# iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE

This way, the laptop is connected to the internet via wlan and to the server via eth0. Also, the laptop is providing an IP address to the server via eth0.

3) Configure DNS server / forward DNS requests with dnsmasq
 So that the server can resolve DNS, the laptop has to be configurated as DNS server or forward the DNS requests that upcome from eth0. The forwarding is neatly done with dnsmasq:

 sudo apt-get install dnsmasq
 sudo dnsmasq -i eth0

 Now, it should be possible to resolve any address in the ARM server:
 

> dig www.google.com (ex.)

[1]: http://wiki.bostonlabs.co.uk/w/index.php/Viridis:Landing_Page
[2]: http://en.wikipedia.org/wiki/Ipmi
[3]: http://en.wikipedia.org/wiki/Preboot_Execution_Environment
[4]: http://wiki.bostonlabs.co.uk/w/index.php/Calxeda:Setup_ipmitool_%26_cxmanage
[5]: http://wiki.bostonlabs.co.uk/w/index.php/External:Setup_a_DHCP_server_for_the_nodes
 
---

Any question/comment/modification contact me - check my contacts @ www.goncalopestana.co - or make a pull request.

**Gonçalo Pestana** 