# This work has been done by Phillip Ochola Mak'Anyengo
# as part of the iHub Research OpenCV Buildathon on the
# <date>
# 
# Email: its2uraps@gmail.com
#
# This work uses open source code and open use libraries
# but the application itself is neither open source or 
# allowed for open use. 
# 
# Users who wish to use parts of this
# work MUST contact the authors before use, failure to which
# the user risks being prosecuted.

#Import all the libraries needed
import time
import numpy as np
import base64
import StringIO
import RPi.GPIO as gpio
import cv2
from autobahn.twisted.websocket import WebSocketServerProtocol, WebSocketServerFactory
from find_obj import filter_matches, explore_match


templates = ['0.png','1.png','2.png','3.png','4.png','5.png','6.png']
templateNames = ['tissue','mouse','myIphone','gamepad','cap','deoderant','cup']
categoryNames = ['green','red','blue']
imageCounter = 0

#Setup the GPIO pins
gpio.setmode(gpio.BOARD)  # use P1 header pin numbering convention
gpio.setwarnings(False)   # don't want to hear about how pins are already in use

gpio.setup(8,gpio.OUT)
gpio.setup(10,gpio.OUT)
gpio.setup(11,gpio.OUT)

#Websocket Event Handling
class MyServerProtocol(WebSocketServerProtocol):
	
	def onConnect(self, request):#Message displayed when there is a connection
		print "Connection opened"

	def onOpen(self):#Message displayed when server opened
		print "WebSocket connection open"
		
	def onMessage(self, payload, isBinary):#Code that runs when message is triggered
		message = format(payload.decode('utf8')) #Message decoded as utf8
		category = 'none'
		global imageCounter
		#To enhance efficiency starting and stopping camera views separated
		#However DO NOT FORGET to close a camera capture
		if (message == '1'):#Start Camera Capture
			print "Starting Camera Capture"
			self.cap = cv2.VideoCapture(0)#Capture Camera
			time.sleep(2)#Time given for camera to start up
			
		if (message == '2'):#Stop Camera capture
			print "Closing Camera Capture"
			self.cap.release()
			
		if (message == '3'):#Multiple Camera displaying algorithms can be added below
			#Remember to refer to video capture as self.cap
			#Replace your own code here. Below is a simple example

			ret,frame = self.cap.read()
			fframe = cv2.flip(frame,1)
			
			
			#The code below sends the captured frame to the Camera viewer. DO NOT DELETE
			#the image is passed to the encoder as frame, you can pass any other image matrix
			encode_param=[1,90]
			res, image = cv2.imencode('.png',fframe,encode_param)
			sample = base64.b64encode(image)
			self.sendMessage(sample, isBinary)
			
		#This algorithm saves an image from the camera. Used for training
		#Hope it works
		if (message == '4'):

			ret,frame = self.cap.read()
			#fframe = cv2.flip(frame,1)

			encode_param=[1,90]
			#res, savingImage = cv2.imencode('.png',fframe,encode_param)
			name = 'capture/' + `imageCounter` +'.png'
			print "Saving Image", name
			cv2.imwrite(name, fframe)
			imageCounter += 1
			self.sendMessage("Saved",isBinary = False)


		#This will take the snap shot and find similarities with the images
		#if it doesnt it replies unknown
		if (message == '5'): #add extra algorithms like this

			ret,frame = self.cap.read()
			fframe = cv2.flip(frame,1)

			j = 0;
			result = "unknown"

			for item in templates:
				tmp = cv2.imread('res/'+item)

				orb = cv2.ORB()
				kp1, des1 = orb.detectAndCompute(fframe,None)
				kp2, des2 = orb.detectAndCompute(tmp,None)

				bf = cv2.BFMatcher(cv2.NORM_HAMMING)#, crossCheck=True)
				matches = bf.knnMatch(des1, trainDescriptors = des2, k=2)

				p1, p2, kp_pairs = filter_matches(kp1, kp2, matches)
	
				i = 0
				m1 = np.array([])
				m2 = np.array([])
				mp_pairs = np.array([])

				for p in p1:
					if(p[0]>266 and p[0]<1014 and p[1]>45 and p[1]<675):
						m1 = np.append(m1, p1[i] - np.array([266,0]), axis=0)
						m2 = np.append(m2, p2[i], axis=0)
						mp_pairs = np.append(mp_pairs, kp_pairs[i], axis=0)
					i+=1

				m1 = np.reshape(m1,(-1,2))
				m2 = np.reshape(m2,(-1,2))

				try:
					homeo = cv2.findHomography(p1,p2, method=0)
				except Exception:
					pass

				stackSize = m1.size / 2
				#print m1/m2
				ratio = np.sum( m1/m2, axis=0)

				#print stackSize, ratio
				try:
					xSim = abs(((stackSize - ratio[0]) / stackSize) * 100)
					ySim = abs(((stackSize - ratio[1]) / stackSize) * 100)
				except:
					pass

				if(~np.isnan(xSim) or ~np.isnan(ySim)):
					print (xSim + ySim)/2
					if (((xSim + ySim)/2) > 80):
						result = templateNames[j]

				print result

				j+=1

			self.sendMessage(result,isBinary = False)
			if category == 'none' :
				gpio.output(8,False)
				gpio.output(10,False)
				gpio.output(11,False)
			elif category == 'green' :
				gpio.output(8,True)
				gpio.output(10,False)
				gpio.output(11,False)
			elif category == 'red' :
				gpio.output(8,False)
				gpio.output(10,True)
				gpio.output(11,False)
			elif category == 'blue' :
				gpio.output(8,False)
				gpio.output(10,False)
				gpio.output(11,True)

				
	def onClose(self, wasClean, code, reason):#Message displayed when there is an error
		print format(reason)


#Start Websocket Server
if __name__ == '__main__':
	import sys
	from twisted.internet import reactor

	factory = WebSocketServerFactory("ws://localhost:5556")#Set debug false to save on processing time
	factory.protocol = MyServerProtocol

	reactor.listenTCP(5556, factory)
	reactor.run()
		

	


