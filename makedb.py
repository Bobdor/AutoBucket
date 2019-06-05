import sqlite3

conn = sqlite3.connect('autobucket.sqlite')
cursor = conn.cursor()
print('Opened Database')
try:
    cursor.execute('''CREATE TABLE DATA
        (ID INT PRIMARY KEY     NOT NULL,
        TIME            DATETIME DEFAULT CURRENT_TIMESTAMP,
        TAIR            NUMERIC    NOT NULL,
        TWATER          NUMERIC    NOT NULL);''')
    cursor.close()
    print('Created Table')
except:
    print('Table already exists')

conn.close()
