from motor import *
import serial

LEFT=0
RIGHT=0
FORWARD=0
BACK=0

ser = serial.Serial(port='COM4',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1)

def signals(self):
    self.LEFT.clicked.connect(self.bt_LEFT)
    self.RIGHT.clicked.connect(self.bt_RiGHT)
    self.FORWARD.clicked.connect(self.bt_FORWARD)
    self.BACK.clicked.connect(self.bt_BACK)

def bt_LEFT(self):
    global LEFT
    if(LEFT):
        message = ''.join(['\x02','L', 'E', 'F', 'T', '\x03'])
        ser.write(bytes(message.encode()))
        LEFT = 0

def bt_RiGHT(self):
    global RIGHT
    if(RIGHT):
        message = ''.join(['\x02','R', 'I', 'G', 'H', 'T','\x03'])
        ser.write(bytes(message.encode()))
        RIGHT = 0


def bt_FORWARD(self):
    global FORWARD
    if(FORWARD):
        message = ''.join(['\x02','F', 'O', 'R', 'W', 'A', 'R','D','\x03'])
        ser.write(bytes(message.encode()))
        FORWARD = 0

def bt_BACK(self):
    global BACK
    if(BACK):
        message = ''.join(['\x02','B', 'A', 'C', 'K', '\x03'])
        ser.write(bytes(message.encode()))
        BACK = 0
  
Ui_MainWindow.signals = signals
Ui_MainWindow.bt_LEFT = bt_LEFT
Ui_MainWindow.bt_RiGHT = bt_RiGHT
Ui_MainWindow.bt_FORWARD = bt_FORWARD
Ui_MainWindow.bt_BACK = bt_BACK

if __name__=="__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    ui.signals()
    MainWindow.show()
    sys.exit(app.exec_())
