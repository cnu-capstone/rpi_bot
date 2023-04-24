#!/bin/bash

# trap "sudo pkill uart_comm" SIGINT
# trap "sudo pkill rpi_routing" SIGINT
trap "sudo pkill demo.sh" SIGINT

while :
do
cd /home/pi/Desktop/AWS/
python awsNotification.py
sleep 1
# cd /home/pi/Documents/rpi_bot/
# ./pi4/uart_comm/uart_comm &
cd /home/pi/Documents/rpi_routing/
./Release/rpi_routing &
sleep 5
# sudo pkill uart_comm
sudo pkill rpi_routing
done
