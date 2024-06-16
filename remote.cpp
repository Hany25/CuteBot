from microbit import*
import radio
import random

radio.on()
x=5
radio.config(group=x)
light = ""
distance = ""
v = 0
e = 0
pressed_pin = 0
pin = 0
touch = 0
z=0
times= 0
w = ""

def receive():
    global light, distance
    light = str(radio.receive())
    distance = str(radio.receive())

def pin_press_handler():
    global pressed_pin
    if pin8.read_digital() == 0:
        pressed_pin = "u"
    elif pin8.read_digital() == 1:
        pressed_pin = "none"
        if pin13.read_digital() == 0:
            pressed_pin = "r"
        elif pin13.read_digital() == 1:
            pressed_pin = "none"
            if pin14.read_digital() == 0:
                pressed_pin = "d"
            elif pin14.read_digital() == 1:
                pressed_pin = "none"
                if pin12.read_digital() == 0:
                    pressed_pin = "l"
                elif pin12.read_digital() == 1:
                    pressed_pin = "none"
        
def mb_led_display():
    global pressed_pin,x
    if (pressed_pin == "u"):
        display.show(Image.ARROW_N)
    elif (pressed_pin == "r"):
        display.show(Image.ARROW_E)
    elif (pressed_pin == "d"):
        display.show(Image.ARROW_S)
    elif (pressed_pin == "l"):
        display.show(Image.ARROW_W)    
    elif (pressed_pin == "none"):
        display.show('x')

def send():
    global pressed_pin, pin,y
    if pressed_pin == "u":
        radio.send("u")
    elif pressed_pin == "r":
        radio.send("r")
    elif pressed_pin == "d":
        radio.send("d")
    elif pressed_pin == "l":
        radio.send("l")
    if pin == "s":
        radio.send("s")
    if touch == "logo":
        radio.send("logo")
    elif touch == "none":
        radio.send("stop")


def distances():
    global distance,e, z
    if distance == ('y'):
        if e == 0:
            display.show("x")
            display.scroll(x)
            z=1
            e=1
    elif e==1 and radio.receive()=="n":
        z=0
        e=0
def vib():
    global z
    if z==0:
        pin1.write_digital(0)
    elif z==1:
        pin0.write_digital(1)
        sleep(250)
        z=0
def lights():
    global light, v
    if light == "low":
        if v == 0:
            v = 1
            pin1.write_digital(1)
            sleep(250)
            pin1.write_digital(0)
    
    elif light == "high":
        v = 0
        pin1.write_digital(0)

def speed():
    global pin
    if pin16.read_digital() ==0:
        pin = "s"
    elif pin16.read_digital() == 1:
        pin = "none"

def touches():
    global touch
    if pin_logo.is_touched() == True:
        touch = "logo"
    elif pin_logo.is_touched() == False:
        touch = "none"

def randoms():
    global x,same, times, w
    if pin15.read_digital() == 0:
        times += 1
        if times <= 3:
            same = x
            while same == x:
                same = random.randint(1,20)
            x = same
            if x < 10:
                w = x
            elif x == 11:
                w = "a"
            elif x == 12:
                w = "b"
            elif x == 13:
                w = "c"
            elif x == 14:
                w = "o"
            elif x == 15:
                w = "e"
            elif x == 16:
                w = "f"
            elif x == 17:
                w = "g"
            elif x == 18:
                w = "h"
            elif x == 19:
                w = "i"
            elif x == 20:
                w = "j"
            elif x == 10:
                w = "k"
            radio.send(str(w))
            radio.config(group=x)
            display.scroll(str(x))
        else:
            radio.send("turn off")
    if button_a.get_presses() > 0:
        x -= 1
        if x == 0:
            x = 1
        display.scroll(x)
        radio.config(group=x)
    if button_b.get_presses() > 0:
        x += 1
        if x == 21:
            x = 20
        display.scroll(x)
        radio.config(group=x)

        
while True:
    receive()
    pin_press_handler()
    randoms()
    mb_led_display()
    distances()
    send()
    lights()
    speed()
    touches()
    vib()
