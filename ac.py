import RPi.GPIO as GPIO


chan_list = (13, 35, 37)
GPIO.output(chan_list, (GPIO.HIGH,GPIO.LOW, GPIO.HIGH)) 