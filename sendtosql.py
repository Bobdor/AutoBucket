import sqlite3
import serial

# open database
conn=sqlite3.connect('autobucket.sqlite')
cursor = conn.cursor()

# open serial port

with serial.Serial('/dev/ttyUSB0', 9600, timeout=10) as ser:
    data=ser.readline()
    

# make a loop to waiting for the data to be sent from the serial connection


conn.commit()
conn.close()
