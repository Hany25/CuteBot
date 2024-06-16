from microbit import *
from cutebot import *
import radio


ct = CUTEBOT()
radio.on()
x = 7
help=0
radio.config(group=x)
z=0
received_str = ""
temp_str = ""
s = 0
move = 40
d=1
l=1
w = ""
def listen_n_receive():

        global received_str, temp_str
        received_str = str(radio.receive())


def speed():

        global received_str, s, move
        if received_str == "s":
            s += 1
        if s == 3:
            s = 0
        if s == 0:
            move = 40
        elif s == 1:
            move = 70
        elif s == 2:
            move = 100


def moves():

        global received_str, s, move
        if received_str == "u":
            ct.set_car_light(left, 235, 143, 52)
            ct.set_car_light(right, 235, 143, 52)
            ct.set_motors_speed(move,move)
        elif received_str == "d":
            ct.set_car_light(left, 52, 235, 229)
            ct.set_car_light(right, 52, 235, 229)
            ct.set_motors_speed(-move,-move)
        elif received_str == "r":
            ct.set_car_light(right, 255, 40, 0)
            ct.set_motors_speed(move, -move)
        elif received_str == "l":
            ct.set_car_light(left, 255, 40, 0)
            ct.set_motors_speed(-move, move)  
        else:
            sleep(75)
            ct.set_motors_speed(0,0)
            ct.set_car_light(right, 0, 0, 0)
            ct.set_car_light(left, 0, 0, 0)


def button():
    global x
    if button_a.get_presses():
        x -= 1
        if x == 0:
            x = 1 
        radio.config(group=x)
        display.show(x)
        sleep(500)
        display.clear
    if button_b.get_presses():
        x += 1
        if x == 21:
            x = 20
        radio.config(group=x)
        display.show(x)
        sleep(500)
        display.clear

def led():

        global x,received_str
        if received_str == "u":
             display.show(Image.ARROW_N)
        elif received_str == "d":
            display.show(Image.ARROW_S)
        elif received_str == "l":
            display.show(Image.ARROW_E)
        elif received_str == "r":
            display.show(Image.ARROW_W)
        elif received_str == "x":
            display.show("x")


def distance():

        global x, z, move
        times = 0
        distance_cm = str(ct.get_distance(0))
        if float(distance_cm) <= 20 and z==0:
            ct.set_motors_speed(0,0)
            radio.send('y')
            display.scroll('x')
            z=1
            times += 1
        elif float(distance_cm) > 20:
            radio.send('n')
            z=0
        if times == 1:
            display.show(x)

        
def logo():

        global received_str, i, help 
        if received_str == "logo":
            while help != 5:
                ct.set_car_light(left,0,255,0)
                ct.set_car_light(right,0,255,0)
                sleep(100)
                ct.set_car_light(left,0,0,0)
                ct.set_car_light(right,0,0,0)
                sleep(100)
                help += 1
        elif received_str!="logo":
            help=0
        elif received_str == "stop":
            return

    

def light():
        light_level = 0
        light_level = display.read_light_level()
        if light_level <= 5:
            radio.send("low")
            ct.set_car_light(right, 255, 255, 255)
            ct.set_car_light(left, 255, 255, 255)
        elif light_level > 5:
            radio.send("high")
            ct.set_car_light(right, 0, 0, 0)
            ct.set_car_light(left, 0, 0, 0)
        
def change_radio():
        global received_str,x,w
        w = received_str
        if received_str.isdigit() == True:
            x = int(received_str)
            received_str = ""
            radio.config(group =x)
            display.scroll(x) 
        elif received_str == "a" or received_str =="b" or received_str =="c" or received_str =="o" or received_str =="e" or received_str =="f" or received_str =="g" or received_str =="h" or received_str =="i" or received_str =="j" or received_str =="k":
            if w == "a":
                x = 11
            elif w == "b":
                x = 12
            elif w == "c":
                x = 13
            elif w == "o":
                x = 14
            elif w == "e":
                x = 15
            elif w == "f":
                x = 16
            elif w == "g":
                x = 17
            elif w == "h":
                x = 18
            elif w == "i":
                x = 19
            elif w == "j":
                x = 20
            elif w == "k":
                x = 10
            received_str = ""
            radio.config(group =x)
            display.scroll(x)
        else:
            return



def shut():

        global received_str, l
        if received_str == "turn off":
            radio.off()
            l = 0

while l==1:
    listen_n_receive()
    speed()
    moves()
    button()
    change_radio()
    led()
    light()
    logo()
    distance()
    shut()
display.clear()
