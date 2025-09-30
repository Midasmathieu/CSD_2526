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
a2 = degrees2 * math.pi / 180
#TODO: take modulo of degrees so if degrees > 360 the pendulum will still trigger the if else statements
time_seconds = float(input("how long do you want the double pendulum to run in seconds"))
time = time_seconds * 60

r1 = 180
r2 = 180
m1 = 0.1
m2 = 0.1
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
g = 1

pygame.mixer.pre_init(44100, -16, 2, 512)
running = True
clock = pygame.time.Clock()
timer = 0
screen = pygame.display.set_mode((windowWidth, windowHeight))
preva1 = a1
preva2 = a2
x2 = 0
prevx2 = x2
kicksound = pygame.mixer.Sound('kick.mp3')
snaresound = pygame.mixer.Sound('snare.mp3')
hihatsound = pygame.mixer.Sound('hihat.mp3')

# alles binnen while running wordt op loop uitgevoerdt.
while running:
    screen.fill((10, 10, 10))
    x1 = r1 * math.sin(a1) + xZero
    y1 = r1 * math.cos(a1) + yZero
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    line1 = pygame.draw.line(screen, (150, 150, 150), (xZero, yZero), (x1, y1))
    line2 = pygame.draw.line(screen, (150, 150, 150), (x1, y1), (x2, y2))
    ball1 = pygame.draw.circle(screen, (100, 100, 100), (x1, y1), m1)
    ball2 = pygame.draw.circle(screen, (100, 0, 100), (x2, y2), m2)
    a1 = a1 + a1_v
    a1_v = a1_v + a1_a
    a2 = a2 + a2_v
    a2_v = a2_v + a2_a
    a1_v = a1_v * 0.995
    a2_v = a2_v * 0.995

# pendulum formula implementation credits: coding thecodingtrain: https://thecodingtrain.com/challenges/93-double-pendulum
    num1 = -g * (2 * m1 + m2) * math.sin(a1)
    num2 = -m2 * g * math.sin(a1 - 2 * a2)
    num3 = -2 * math.sin(a1 - a2) * m2
    num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * math.cos(a1 -a2)
    den = r1 * (2 * m1 + m2 - m2 * math.cos(2 * a1 - 2 * a2))
    a1_a = (num1 + num2 + num3 * num4) / den

    num1 = 2 * math.sin(a1 - a2)
    num2 = (a1_v * a1_v * r1 * (m1 + m2))
    num3 = g * (m1 + m2) * math.cos(a1)
    num4 = a2_v * a2_v * r2 * m2 * math.cos(a1 - a2)
    dev = r2 * (2 * m1 + m2 - m2 * math.cos(2 * a1 - 2 * a2))
    a2_a = (num1 * (num2 + num3 + num4)) / den


    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    # print(a1 % math.pi)
    def crossing(angle, prevangle, drumsound, min, max):
        if (angle % math.pi) > max and (prevangle % math.pi) < min:
            drumsound.play()
        if (angle % math.pi) < min and (prevangle % math.pi) > max:
            drumsound.play()
    print(x2)
    if x2 > 400 and prevx2 < 400:
        snaresound.play()
        print("hahadfsdhdfashkjldfjhkls")
    if x2 < 400 and prevx2 > 400:
        snaresound.play()

    crossing(a1, preva1, kicksound, 0.2, 3.0)
    crossing(a2, preva2, hihatsound, 0.2, 3.0)
    crossing(x1, prevx2, snaresound, 0.2, 3.0)


    pygame.display.flip()

    clock.tick(60)
    timer = timer + 1
    preva1 = a1
    preva2 = a2
    prevx2 = x2
    # print(a1 % math.pi)

    if timer > time:
        running = False



pygame.quit()

# next_step = input("DOYAWANNATEEKDANEXTSTEP? ")
