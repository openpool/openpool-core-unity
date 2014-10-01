#! /usr/bin/env python
# -*- coding: utf-8 -*-

'''
OscTest.py
'''

# osc.sendMsg("/calibration", [-0.03, -0.07, 0.07, 0.0, 0.0, 0.5, 0.0, 0.0, 1.0, 1.0], "192.168.2.76", 7000)

import osc

class OpenPool:
	def __init__(self, ipAddress):
		osc.init()
		self.address = ipAddress
		self.port = 7000
		self.frame = 0
		print ("address : ",ipAddress)

	def sendOsc(self, url, params):
		osc.sendMsg(url, params, self.address, self.port)
		print ("send : ", url, " : ", params)

	def sendBall(self, x,y):
		if self.frame >= 100:
			self.frame = 0
		else:
			self.frame += 1
		self.sendOsc("/ball", [self.frame, x, y])


	def sendPocket(self, id):
		self.sendOsc("/pocket", [id, 1])

	def sendCollision(self):
		self.sendOsc("/collision", [0.1])

	def sendQueue(self):
		self.sendOsc("/queue", [0])



if __name__ == '__main__':
	import sys
	import time

	argvs = sys.argv
	argc  = len(argvs)

	if len(argvs) <= 1:
		address = "127.0.0.1"	
	else:
		address = argvs[1]

	op = OpenPool(address)

	# ball position test
	time.sleep(1)
	op.sendBall(0.1, 0.1)
	time.sleep(0.05)
	op.sendBall(0.2, 0.2)
	time.sleep(0.05)
	op.sendBall(0.3, 0.3)
	time.sleep(0.05)
	op.sendBall(0.4, 0.4)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)

	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)
	time.sleep(0.05)
	op.sendBall(0.5, 0.5)

	# pocket in test
	time.sleep(1)
	op.sendPocket(0)
	time.sleep(1)
	op.sendPocket(1)
	time.sleep(1)
	op.sendPocket(2)
	time.sleep(1)
	op.sendPocket(3)
	time.sleep(1)
	op.sendPocket(4)
	time.sleep(1)
	op.sendPocket(5)

	# collision
	time.sleep(1)
	op.sendCollision()
	time.sleep(1)
	op.sendCollision()
	time.sleep(1)
	op.sendCollision()
	time.sleep(1)
	op.sendCollision()
