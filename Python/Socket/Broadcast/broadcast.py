from socket import *
from get_ip_addr import *
    
s=socket(AF_INET, SOCK_DGRAM)
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
# s.sendto(str(gethostbyname(gethostname())),('255.255.255.255',12345))
s.sendto(str(get_ip_address()),('255.255.255.255',12345))
