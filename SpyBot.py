#libraries

import sys
import serial
import time
import pygame
import pygame.camera
from pygame.locals import *

#var------------------------------------------------------------------------------------------------------

exitGame = False
user_input = 'L'
display_width = 1200
display_height = 800

#colours -------------------------------------------------------------------------------------------------

white = (255,255,255)
black = (0,0,0)
red = (255,0,0)

#imports for serial connection-----------------------------------------------------------------------------

port = '/dev/ttyUSB0'
ser = serial.Serial(port, 9600, timeout=1)
time.sleep(2)

#pygame and pycam init--------------------------------------------------------------------------------------

pygame.init()
pygame.camera.init()

screen = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('project W upd')

cam = pygame.camera.Camera("/dev/video0",(int(display_width/1.875),int(display_height/1.667)))
cam.start()

#font----------------------------------------------------------------------------------------------------------

font=pygame.font.SysFont(None,40)

#main game-------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------
while exitGame != True :
    
#exit
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    
#passive events--------------------------------
    screen.fill(red)
    

    
    user_input = 't'
    ser.write(user_input.encode())
    rec_data_raw = ser.readline()  
    time.sleep(0.1) 
    string_n = rec_data_raw.decode()   
    string = string_n.rstrip() 
    rec_data = str(string)
    label_temp = font.render('Temperature : ',True, black)
    screen.blit(label_temp,[700,50])   

    rec_temp_pr = font.render(rec_data,True, black)
    screen.blit(rec_temp_pr,[900,50])
    
    label_c = font.render('oC ',True, black)
    screen.blit(label_c,[1000,50])
    
    
    pygame.display.update
    

            
    #camera
    image = cam.get_image()
    screen.blit(image,(0,0))
    pygame.display.update()
    
    #active events------------------------------------
    
    if event.type ==pygame.KEYDOWN:
        if event.key == 113:
          sys.exit()
        if event.key == 119:
          user_input = 'w'
          ser.write(user_input.encode())   # forward
          time.sleep(0.1) 
          
        elif event.key == 32:
          user_input = 'p'
          ser.write(user_input.encode())   # stop(space)
          time.sleep(0.1) 
          
        elif event.key == 115:
          user_input = 's'
          ser.write(user_input.encode())   # backward
          time.sleep(0.1)            
    
        elif event.key == 97:
          user_input = 'a'
          ser.write(user_input.encode())   # left
          time.sleep(0.1)
          
        elif event.key == 100:
          user_input = 'd'
          ser.write(user_input.encode())   # right
          time.sleep(0.1)
          
        elif event.key == 101:
          user_input = 'e'
          ser.write(user_input.encode())   # led_tape
          time.sleep(0.1)
