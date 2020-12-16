from GUI import *
from PyQt5 import QtCore, QtGui, QtWidgets
import pygame
import threading
import serial
import time
pygame.init()
pygame.mixer.init()


ser = serial.Serial(port='COM7',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1)

def signals(self):
    cnt = 0
    
    
    
def Danger(self):
    while True:
        ser_data = ser.readline()
        if(ser_data):
            print(ser_data)
            if ser_data[0:7] == "Danger":
                cnt = 1
            else:
                cnt = 0
            if cnt == 1:
                self.color.setStyleSheet("background-color : red; border-radius : 50%;")
                self.label.setText("침입 감지")
                import pygame
                pygame.init()
                sounda = pygame.mixer.Sound('sound2.wav')
                sounda.play()

            elif cnt == 0:
                self.color.setStyleSheet("background-color : blue; border-radius : 50%;")
                self.label.setText("침입이 감지되었습니다 ")

            




Ui_MainWindow.signals = signals
Ui_MainWindow.Danger = Danger


if __name__=="__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    ui.signals()
    th = threading.Thread(target = Danger,args=(ui,))
    th.daemon = True
    th.start()
   
    MainWindow.show()
    sys.exit(app.exec_())