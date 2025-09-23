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
a1 = 0
a2 = 0
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
running = True
clock = pygame.time.Clock()
delta_time = 0.1
screen = pygame.display.set_mode((windowWidth, windowHeight))

# alles binnen while running wordt op loop uitgevoerdt.
while running:
    x1 = r1 * math.sin(a1) + xZero
    y1 = r1 * math.cos(a1) + yZero
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    line1 = pygame.draw.line(screen, (150, 150, 150), (xZero, yZero), (x1, y1))
    line2 = pygame.draw.line(screen, (150, 150, 150), (x1, y1), (x2, y2))
    ball1 = pygame.draw.circle(screen, (100, 100, 100), (x1, y1), m1)
    ball2 = pygame.draw.circle(screen, (100, 0, 100), (x2, y2), m2)



















    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

    delta_time = clock.tick(60)
    delta_time = max(0.001, min(0.1, delta_time))

pygame.quit()
