#!./bin/python
from swampy.TurtleWorld import *
import math
world = TurtleWorld()

def square(t , length):
    for i in range(4):
        fd(t , length)
        lt(t) # lt(t , degree)

def polygon(t , n , length , polyg = 0):
    """Draws n line segments with the given length and angle (in degrees)
    between them. t is a turtle. """
    if(polyg == 0):
        polyg = n
    for i in range(polyg):
        fd(t , length)
        lt(t , 360.0/n)

def circle(t , r):
    n = 20
    inter_angle = 360.0/n
    length = math.sqrt(2*(r**2)*(1 - math.cos(inter_angle)))
    polygon(t , n ,length)

def arc(t , r , angle):
    n = 20
    inter_angle = 360.0/n
    length = math.sqrt(2*(r**2)*(1 - math.cos(inter_angle)))
    polyg = int(angle / inter_angle)
    polygon(t , n ,length ,polyg)





def main():
    bob = Turtle()
    bob.delay = 0.01
    arc(bob , 20 , 300)
    #circle(bob , 20)
    #polygon(bob , 15 , 100)
    #square(bob , 40)

if __name__ == '__main__':
    main()
wait_for_user()
