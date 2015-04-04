#!/usr/bin/python

# Scapy Webserver
# Author:  fleevee
# Date:  4/31/2015

from scapy.all import *

# Wait for the SYN from the client
syn = sniff(count = 1, filter = "tcp and host 10.0.1.32 and port 80")

print syn[0].src

port = syn[0].sport
seq = syn[0].seq
ack_seq = seq + 1

# Generating IP Layer
ip = IP(src = "10.0.1.32", dst = "10.0.1.56")

# Generating TCP Layer
synack = TCP(sport = 80, dport = port, flags = "SA", seq = seq, ack = ack_seq, options = [('MSS', 1460)])

# Send SYNACK, wait for ACK from the client
ack = sr1(ip/synack)

# Wait for HTTP GET Request from the client
get = sniff(filter = "tcp and port 80", count = 1, prn = lambda x:x.sprintf("{IP:%IP.src%: %TCP.dport%}"))

ack_seq += len(get[0].load)
seq += 1

# Print HTTP GET Request
if (len(get[0].load) > 1): print get[0].load

# Generating HTML data
html = "HTTP/1.1 200 OK\nDATE: 4/31/2015\nServer: Scapy Webserver\nConnection: Keep-Alive\nContent-Type: text/html; charset=UTF-8\nContent-Length: 291\n\n<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\"><html><head><title>Scapy Webserver</title></head><body bgcolor=\"black\" text=\"white\" link=\"blue\" vlink=\"purple\" alink=\"red\"><p><font face=\"Courier\" color=\"green\">-Welcome to fleevee's Scapy Webserver!-</font></p></body></html>"

# Generating TCP data
data = TCP(sport = 80, dport = port, flags = "PA", seq = seq, ack = ack_seq, options = [('MSS', 1460)])

# Send HTTP Response, wait for ACK from the client
ack2 = sr1(ip/data/html)

seq = ack2.ack

# Generating RST-ACK
bye = TCP(sport = 80, dport = port, flags = "FA", seq = seq, ack = ack_seq, options = [('MSS', 1460)])

# Send Goodbye
send(ip/bye)