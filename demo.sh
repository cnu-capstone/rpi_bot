#!/bin/bash

trap "sudo pkill uart_comm" SIGINT
cd /home/pi/Documents/rpi_bot/

while :
do
cd AWS/
python awsNotification.py
sleep 1
./pi4/uart_comm/uart_comm &
sleep 5
sudo pkill uart_comm
done
