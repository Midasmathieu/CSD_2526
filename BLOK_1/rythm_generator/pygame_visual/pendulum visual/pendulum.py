import pygame
import math
pygame.init()
windowWidth = 800
windowHeight = 800
xZero = windowWidth / 2
yZero = windowHeight / 2
r1 = 100
r2 = 100
m1 = 10
m2 = 10
a1 = 1
a2 = 0
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
g = 1

running = True
clock = pygame.time.Clock()
delta_time = 0.1
screen = pygame.display.set_mode((windowWidth, windowHeight))

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
    a1_v = a1_v + a1_a * delta_time
    a2 = a2 + a2_v
    a2_v = a2_v + a2_a * delta_time

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


















    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

    delta_time = clock.tick(60)
    delta_time = max(0.001, min(0.1, delta_time))

pygame.quit()
