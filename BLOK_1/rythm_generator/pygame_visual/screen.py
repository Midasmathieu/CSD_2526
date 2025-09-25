import pygame

pygame.init()
schermpje = 750

screen = pygame.display.set_mode((schermpje, schermpje))

ableton_img = pygame.image.load('ableton.png').convert_alpha()

ableton_img = pygame.transform.scale(ableton_img,
                                    (ableton_img.get_width() / 2,
                                     ableton_img.get_height() /2))

running = True
x = 100
y = 100
vx = 100
vy = 100
ballx = 100
bally = 100
vBallx = -300
vBally = 200
stroal = 20

clock = pygame.time.Clock()

delta_time = 0.1

while running:
    screen.fill((0, 0, 0))
    screen.blit(ableton_img, (x, y))

    ball = pygame.draw.circle(screen, (100, 100, 100), (ballx,bally), stroal)
    x += vx * delta_time
    y += vy * delta_time
    ballx += vBallx * delta_time
    bally += vBally * delta_time


    if ballx > schermpje - stroal:
        vBallx = vBallx * -1
        # stroal = 10

    if ballx < stroal:
        vBallx = vBallx * -1
        # stroal = 10

    if bally > schermpje - stroal:
        vBally = vBally * -1
        # stroal = 10

    if bally < stroal:
        vBally = vBally * -1
        # stroal = 10

    if x > schermpje - ableton_img.get_width():
        vx = vx * -1

    if x < 0:
        vx = vx * -1

    if y > schermpje - ableton_img.get_height():
        vy = vy * -1

    if y < 0:
        vy = vy * -1

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

    delta_time = clock.tick(60) / 1000
    delta_time = max(0.001, min(0.1, delta_time))

pygame.quit()
