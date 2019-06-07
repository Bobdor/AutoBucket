import serial
import sqlite3
from datetime import datetime

conn = sqlite3.connect('autobucket.sqlite')
cursor = conn.cursor()
print('Opened Database')
try:
    cursor.execute('''CREATE TABLE DATA
        (ID           INTEGER PRIMARY KEY NOT NULL,
        TIME          DATETIME DEFAULT CURRENT_TIMESTAMP,
        PH            NUMERIC    NOT NULL,
        TAIR          NUMERIC    NOT NULL);''')
    cursor.close()
    print('Created Table')
except:
    print('Table already exists')

def getData():
        with serial.Serial('/dev/ttyUSB0', 9600, timeout=10) as ser:
                while 1==1:
                        data=ser.readline().decode('utf8')
                        ph = data.split(':')[1]
                        airTemp = data.split(':')[0]
                        params = (ph,airTemp)
                        cursor.execute("INSERT INTO DATA (PH,TAIR) VALUES (?,?)", params);
                        conn.commit()

getData()
