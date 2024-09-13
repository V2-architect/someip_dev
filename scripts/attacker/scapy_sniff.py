from scapy.all import *
import pdb

multicast_group = "239.10.0.1"
multicast_port = 30490

server_ip = "10.0.0.1"
client2_ip = "10.0.0.2"
client3_ip = "10.0.0.3"

client3_mac = getmacbyip(client3_ip)
print(f"client3_mac: {client3_mac}")

def process_packet(packet):
    print("hit!")
    if packet.haslayer(IP) and packet.haslayer(UDP):
        if packet[IP].src == server_ip and packet[IP].dst == multicast_group:
            print("if-if statement!")
            print(f"Sniffed packet from {packet[IP].src} to {packet[IP].dst}")
            payload = packet[Raw].load
            #original_payload = packet[Raw].load.decode()
            #print(f"Original Payload: {original_payload}")
            
            #modified_payload = "2"
            #packet[Raw].load = modified_payload.encode()

            #[1] not working
            #packet = Ether(dst="01:00:5e:0a:00:01") / IP(src="10.0.0.3", dst="239.10.0.1") / UDP(dport=30490) / Raw(load=payload)

            #[2] wrong working
            #packet[IP].src = client3_ip
            #eth = Ether(dst=client3_mac)
            #packet = eth / packet
            #del packet[IP].chksum
            #del packet[UDP].chksum
            
            send(packet)
            print("send1")
            send(packet)
            print("send2")
            send(packet)
            print("send3")
            send(packet)
            print("send4")
            pdb.set_trace()
            #print(f"Modified Payload sent as: {modified_payload}")

#sniff(filter=f"udp and src dst {multicast_group} and src port {multicast_port}", iface='client3-eth0', prn=process_packet)
sniff(filter=f"udp and src host 10.0.0.1 and src port 30490", iface='client3-eth0', prn=process_packet)
#udp and src host {node1_ip} and src port {node1_port}

