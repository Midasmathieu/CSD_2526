import pygame
import math
import time as t



pygame.init()
windowWidth = 800
windowHeight = 800
screen = pygame.display.set_mode((windowWidth, windowHeight))
clock = pygame.time.Clock()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)
timer = 0

kickSound = pygame.mixer.Sound('dark_kick.mp3')
snareSound = pygame.mixer.Sound('dark_snare.mp3')
hihatSound = pygame.mixer.Sound('dark_hat.mp3')

pendulumDict = {
    'xZero': 0,
    'yZero': 0,
    'r1': 180,
    'r2': 180,
    'm1': 0.1,
    'm2': 0.1,
    'a1': 90,
    'a2': 90,
    'a1_v': 0,
    'a2_v': 0,
    'a1_a': 0,
    'a2_a': 0,
    'g': 1,
    'x1': 0,
    'y1': 0,
    'x2': 0,
    'y2': 0,
    'prevA1': 0,
    'prevA2': 0,
    'prevX2': 0

}

xZero = windowWidth / 2
pendulumDict['xZero'] = xZero
yZero = windowHeight / 2 - 20
pendulumDict['yZero'] = yZero

pendulumDict['prevA1'] = (pendulumDict.get('a1'))
pendulumDict['prevA2'] = (pendulumDict.get('a2'))

kick = []
snare = []
hihat = []
velocityList = []

# calculates the lines of the pendulum and draws them
def calculatePendulumPos(pendulumDict):
    r1 = float(pendulumDict.get('r1'))
    r2 = float(pendulumDict.get('r2'))
    a1 = float(pendulumDict.get('a1'))
    a2 = float(pendulumDict.get('a2'))
    xZero = int(pendulumDict.get('xZero'))
    xZero = int(pendulumDict.get('xZero'))
    x1 = r1 * math.sin(a1) + xZero
    y1 = r1 * math.cos(a1) + yZero
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    pendulumDict['x1'] = x1
    pendulumDict['y1'] = y1
    pendulumDict['x2'] = x2
    pendulumDict['y2'] = y2
    return 0

def pendulumDraw(pendulumDict):
    xZero = int(pendulumDict.get('xZero'))
    xZero = int(pendulumDict.get('xZero'))
    x1 = float(pendulumDict.get('x1'))
    y1 = float(pendulumDict.get('y1'))
    x2 = float(pendulumDict.get('x2'))
    y2 = float(pendulumDict.get('y2'))
    screen.fill((10, 10, 10))
    line1 = pygame.draw.line(screen, (150, 150, 150), (xZero, yZero), (x1, y1))
    line2 = pygame.draw.line(screen, (150, 150, 150), (x1, y1), (x2, y2))
    pygame.display.flip()
    return 0

def calculatePendulumAngle(pendulumDict, deltaTime):
    m1 = float(pendulumDict.get('m1'))
    m2 = float(pendulumDict.get('m2'))
    a1 = float(pendulumDict.get('a1'))
    a2 = float(pendulumDict.get('a2'))
    a1_v = float(pendulumDict.get('a1_v'))
    a2_v = float(pendulumDict.get('a2_v'))
    a1_a = float(pendulumDict.get('a1_a'))
    a2_a = float(pendulumDict.get('a2_a'))
    g = float(pendulumDict.get('g'))
    r1 = float(pendulumDict.get('r1'))
    r2 = float(pendulumDict.get('r2'))
    xZero = int(pendulumDict.get('xZero'))
    xZero = int(pendulumDict.get('xZero'))

    a1 = (a1 + a1_v) % (2 * math.pi)
    a1_v = a1_v + a1_a
    a2 = (a2 + a2_v) % (2 * math.pi)
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

    pendulumDict['a1_v'] = a1_v
    pendulumDict['a2_v'] = a2_v
    pendulumDict['a1_a'] = a1_a
    pendulumDict['a2_a'] = a2_a
    pendulumDict['a1'] = a1
    pendulumDict['a2'] = a2
    return pendulumDict

def pendulumHistory(pendulumDict):
    a1 = float(pendulumDict.get('a1'))
    a2 = float(pendulumDict.get('a2'))
    x2 = float(pendulumDict.get('x2'))
    pendulumDict['prevA1'] = a1
    pendulumDict['prevA2'] = a2
    pendulumDict['prevX2'] = x2
    return a1, a2, x2



def crossing(angle, prevangle, drumsound, min, max, list, angleVelocity):
    if angle > max and prevangle < min:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 50
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(timer)
        # print("velocity: ", noteVelocity)
        print(angle)
    if angle < min and prevangle > max:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 50
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(timer)
        # print("velocity: ", noteVelocity)
        print(angle)


# def crossing(angle, prevangle, drumsound, min, max)

def playNote(sample, velocity):
    sample.set_volume(velocity / 127.0)
    sample.play()


#GAMELOOP!
running = True
while running == True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    klokje = clock.tick(60)
    timer = timer + (klokje / 1000)

    screen.fill((10, 10, 10))
    # line3 = pygame.draw.line(screen, (200, 0, 150), (0, 100), (yes, no))
    calculatePendulumPos(pendulumDict)
    pendulumDraw(pendulumDict)
    calculatePendulumAngle(pendulumDict, klokje)
    crossing(pendulumDict.get('a1'), pendulumDict.get('prevA1'), kickSound, 0.5, 2.6, kick, pendulumDict['a1_v'])
    crossing(pendulumDict.get('a2'), pendulumDict.get('prevA2'), hihatSound, 0.5, 2.6, hihat, pendulumDict['a2_v'])
    crossing(pendulumDict.get('x2'), pendulumDict.get('prevX2'), snareSound, pendulumDict.get('xZero'), pendulumDict.get('xZero'), snare, pendulumDict['a2_v'])
    pendulumHistory(pendulumDict)
    # print(prevA1, prevX1, prevX2)
    # crossing(a)

    pygame.display.flip()

pygame.quit()
