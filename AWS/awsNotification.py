import time
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
from threading import Event
import requestLocation

exit = Event()


def helloworld(self, params, packet):
	print("Received Message form AWS IO Core")
	print("Topic:",packet.topic)
	print("Payload:",(packet.payload))
	#file = open("/home/pi/Desktop/AWS/location.txt","w")
	file = open("/home/pi/Documents/rpi_bot/AWS/location.txt","w")
	value=str(packet.payload).replace("b","")
	value2 =value.replace('"',"")
	file.write(value2.replace("'",""))
	file.close()
	#print("should be in the location.txt")

requestLocation.main()
myMQTTClient = AWSIoTMQTTClient("RaspPI_id")
myMQTTClient.configureEndpoint("a117fkprmo513-ats.iot.us-east-1.amazonaws.com", 8883) #Provide your AWS IoT Core endpoint (Example: "abcdef12345-ats.iot.us-east-1.amazonaws.com")


myMQTTClient.configureCredentials("/home/pi/Documents/rpi_bot/AWS/certs/AmazonRootCA1.pem", "/home/pi/Documents/rpi_bot/AWS/certs/806f08c1d1530e5f30d445233258e5403f7a43e0595336fb46cec2067e54c9c7-private.pem.key", "/home/pi/Documents/rpi_bot/AWS/certs/806f08c1d1530e5f30d445233258e5403f7a43e0595336fb46cec2067e54c9c7-certificate.pem.crt") #Set path for Root CA and provisioning claim credentials

myMQTTClient.configureOfflinePublishQueueing(-1)
myMQTTClient.configureDrainingFrequency(2)
myMQTTClient.configureConnectDisconnectTimeout(10)
myMQTTClient.configureMQTTOperationTimeout(5)
 
print("Initiating IoT Core Topic ...")
myMQTTClient.connect()
print("connected")
myMQTTClient.subscribe("$aws/things/pi/shadow/update", 1, helloworld)

time.sleep(5)

