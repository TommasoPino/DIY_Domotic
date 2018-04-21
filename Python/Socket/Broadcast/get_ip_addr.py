from socket import *

def get_ip_address():
    ip_address = '';
    s = socket(AF_INET, SOCK_DGRAM)
    s.connect(("8.8.8.8",80))
    ip_address = s.getsockname()[0]
    s.close()
    return ip_address