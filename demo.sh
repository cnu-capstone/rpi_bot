#!/bin/bash

while :
do
cd /home/pi/Desktop/AWS/
python awsNotification.py
sleep 1
cd /home/pi/Documents/rpi_bot/
./pi4/uart_comm/uart_comm
PID=$!
sleep 1
kill -INT $PID
done
