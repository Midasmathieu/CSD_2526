import pygame
import math
pygame.init()
windowWidth = 800
windowHeight = 800
xZero = windowWidth / 2
yZero = windowHeight / 2 - 20

#credits for all the math implementation of the pendulum to the coding train (https://thecodingtrain.com/challenges/93-double-pendulum)
degrees1 = float(input("where do you want pendulum1 to start in degrees?: "))
a1 = degrees1 * math.pi / 180
degrees2 = float(input("where do you want pendulum2 to start in degrees?: "))
a2 = degrees1 * math.pi / 180
#TODO: take modulo of degrees so if degrees > 360 the pendulum will still trigger the if else statements
time_seconds = float(input("how long do you want the double pendulum to run in seconds"))
time = time_seconds * 60

r1 = 180
r2 = 180
m1 = 1
m2 = 1
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
g = 1

running = True
clock = pygame.time.Clock()
timer = 0
screen = pygame.display.set_mode((windowWidth, windowHeight))
preva1 = a1
x1 = 0
prevx1 = 0

# alles binnen while running wordt op loop uitgevoerdt.
while running:
    screen.fill((10, 10, 10))
    x1 = r1 * math.sin(a1) + xZero
    y1 = r1 * math.cos(a1) + yZero
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    line1 = pygame.draw.line(screen, (150, 150, 150), (xZero, yZero), (x1, y1))
    line2 = pygame.draw.line(screen, (150, 150, 150), (x1, y1), (x2, y2))
    # ball1 = pygame.draw.circle(screen, (100, 100, 100), (x1, y1), m1)
    # ball2 = pygame.draw.circle(screen, (100, 0, 100), (x2, y2), m2)
    a1 = a1 + a1_v
    a1_v = a1_v + a1_a
    a2 = a2 + a2_v
    a2_v = a2_v + a2_a
    a1_v = a1_v * 0.995
    a2_v = a2_v * 0.995

    num1 = -g * (2 * m1 + m2) * math.sin(a1)
    num2 = -m2 * g * math.sin((a1 - 2 * a2))
    num3 = -2 * math.sin((a1 - a2)) * m2
    num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * math.cos((a1 -a2))
    den = r1 * (2 * m1 + m2 - m2 * math.cos(2 * a1 - 2 * a2))
    a1_a = (num1 + num2 + num3 * num4) / den

    num1 = 2 * math.sin((a1 - a2))
    num2 = (a1_v * a1_v * r1 * (m1 + m2))
    num3 = g * (m1 + m2) * math.cos(a1)
    num4 = a2_v * a2_v * r2 * m2 * math.cos(a1 - a2)
    dev = r2 * (2 * m1 + m2 - m2 * math.cos((2 * a1 - 2 * a2)))
    a2_a = (num1 * (num2 + num3 + num4)) / den
    if x1 > 0 and prevx1 < 0:
        # kick.append(millisec)
        print(check)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

    clock.tick(60)
    timer = timer + 1
    # print(a1 % math.pi)
    if (a1 % math.pi) > 0 and (preva1 % math.pi) < 0:
        print("aaaaaaaaaaaaä")

    if timer > time:
        running = False

    preva1 = a1
    prevx1 = x1

pygame.quit()

next_step = input("DOYAWANNATEEKDANEXTSTEP? ")
