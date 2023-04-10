#!/bin/bash

trap "sudo pkill uart_comm" SIGINT

while :
do
cd /home/pi/Desktop/AWS/
python awsNotification.py
sleep 1
cd /home/pi/Documents/rpi_bot/
./pi4/uart_comm/uart_comm &
sleep 5
sudo pkill uart_comm
done
