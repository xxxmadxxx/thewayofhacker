Server IP: 10.10.11.247

Port 21/tcp is open (vsFTPd 3.0.3)  - Anonymous login allowed. Maybe we could exploit it
Port 22/tcp open  ssh
Port 53/tcp open  domain

Root password ?

/etc/config/rpcd - Not able to login with ssh 

/etc/config/wireless - has password (VeRyUniUqWiFIPasswrd1!)


- The password found in wireless file can be used with the user netadmin to login in ssh
- We have found a vulnerability in WPS - https://github.com/t6x/reaver-wps-fork-t6x

