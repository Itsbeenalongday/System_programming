import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

trig = 17
echo = 18

GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)

try:
	while 1:
		GPIO.output(trig, False)
		time.sleep(0.5)
		print('here1')
		GPIO.output(trig, True)
		time.sleep(0.00001)
		GPIO.output(trig, False)
		print('here2')
		while GPIO.input(echo) == False:
			pulse_start = time.time()
		print('here3')
		while GPIO.input(echo) == True:
			pulse_end = time.time()
		print('here4')
		pulse_duration = pulse_end - pulse_start
		print('here5')
		distance = pulse_duration * 17000
		print('here6')
		distance = round(distance, 2)
		print('here7')
		print("Distance : ", distance, "cm")
          
except:
	GPIO.cleanup()
