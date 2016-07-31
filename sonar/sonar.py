#!/usr/bin/env python3
import math
import pygame
import pygame.gfxdraw
import time

pygame.init()
 
background_color    = [ 0,   0,   0 ]
sweep_color         = [ 0,   120, 0 ]
outer_border_color  = [ 10,  55,  10 ]
outer_circle_color  = [ 10,  45,  10 ]
inner_border_color  = [ 10,  85,  10 ]
inner_circle_color  = [ 100, 95,  10 ]
grid_color          = [ 80,  80,  80 ]

screen_width = 600
screen_height = 600
outer_border_width = 12
inner_border_width = 9

screen = pygame.display.set_mode((screen_width,screen_height))
midpoint = [ int(screen_width/2), int(screen_height/2) ]
radius = midpoint[0]
sweep_length = radius - outer_border_width
 
my_clock = pygame.time.Clock()
 
done = False
angle = 0
sweep_speed = .005
valid_width = 0
valid_height = 0
pi = 3.141592653

def calcRotation(angle):
    x = sweep_length * math.sin(angle) + int(screen_width/2)
    y = sweep_length * math.cos(angle) + int(screen_height/2)
    angle = angle - sweep_speed
 
    if angle < (-2 * pi):
        angle = angle + (2 * pi)

    return [x, y, angle]

def drawGrid():
    screen.fill(background_color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], radius, outer_border_color)
    pygame.gfxdraw.filled_ellipse(screen, midpoint[0], midpoint[1], radius, radius, outer_border_color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], radius - outer_border_width, outer_circle_color)
    pygame.gfxdraw.filled_ellipse(screen, midpoint[0], midpoint[1], radius - outer_border_width, radius - outer_border_width, outer_circle_color)
    pygame.draw.line(screen, [128, 128, 128], [screen_width/2,outer_border_width], [screen_width/2,screen_height-outer_border_width], 1)
    pygame.draw.line(screen, [128, 128, 128], [outer_border_width,screen_height/2], [screen_width-outer_border_width,screen_height/2], 1)

    [tx, ty] = [sweep_length * math.sin(pi/4) + int(screen_width/2), sweep_length * math.cos(pi/4) + int(screen_height/2)]
    [tx2, ty2] = [-tx + int(screen_width), -ty + int(screen_height)]
    pygame.draw.line(screen, grid_color, [tx2, ty2], [tx, ty], 1)
    pygame.draw.line(screen, grid_color, [tx, ty2], [tx2, ty], 1)

    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], screen_width/4, grid_color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], 3*screen_width/8, grid_color)

def drawInnerCircle():
    global valid_width, valid_height

    inner_circle_radius = int(radius/5)
    valid_width = (screen_width - inner_circle_radius) / 2
    valid_height = (screen_height - inner_circle_radius) / 2

    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], inner_circle_radius, inner_border_color)
    pygame.gfxdraw.filled_ellipse(screen, midpoint[0], midpoint[1], inner_circle_radius, inner_circle_radius, inner_border_color)

    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], inner_circle_radius - inner_border_width, inner_circle_color)
    pygame.gfxdraw.filled_ellipse(screen, midpoint[0], midpoint[1], inner_circle_radius - inner_border_width, inner_circle_radius - inner_border_width, inner_circle_color)

def mustQuit():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            return True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                return True
    return False

blipImage = pygame.image.load("blip.png").convert_alpha()
start_time = time.time()
foundBlip = False
blipAngle = 0

while done == False:
    done = mustQuit()
    drawGrid()

    [x, y, angle] = calcRotation(angle)
    pygame.draw.line(screen, sweep_color, midpoint, [x, y], 4)

    drawInnerCircle()
    # x = midpoint[0] + (valid_width * distance) / max_distance

    if (foundBlip):
        if ((time.time() - start_time) <= 1):
            screen.blit(blipImage, ((midpoint[0] + ((valid_width * 200) / 400) * math.sin(blipAngle)), (midpoint[1] + ((valid_height * 200) / 400) * math.cos(blipAngle))))

    if ((time.time() - start_time) >= 2):
        foundBlip = True
        blipAngle = angle
        start_time = time.time()

    pygame.display.update()
    my_clock.tick(60)

pygame.quit()
