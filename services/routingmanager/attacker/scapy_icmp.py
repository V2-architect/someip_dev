from scapy.all import *

src_ip = "10.0.0.3"
dst_ip = "239.10.0.1"

icmp_request = IP(src=src_ip, dst=dst_ip, ttl=64) / ICMP()

send(icmp_request)

