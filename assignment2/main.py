from raster.grid import *
from math import floor, ceil

def rasterline(x1,y1,x2,y2):

    # Make sure that x2 is the biggest value
    if(x1 > x2):

        # This is the only good way to swap variables
        # https://docs.python.org/3/reference/expressions.html#evaluation-order
        x1, x2 = x2, x1
        y1, y2 = y2, y1

    # Calculate the tangent
    a = (y2-y1) / (x2-x1)

    # Put points in place
    for x in range(x1,x2+1):
        y = floor(a * (x - x1)) + y1
        g.addPoint(x,y)

g = Grid(20, 10)

rasterline(2, 1, 15, 4)

g.draw()
