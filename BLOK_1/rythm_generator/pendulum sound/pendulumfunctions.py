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

kick = []
snare = []
hihat = []

r1 = 180
r2 = 180
m1 = 0.1
m2 = 0.1
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
g = 1
x1 = r1 * math.sin(a1) + xZero
y1 = r1 * math.cos(a1) + yZero
x2 = x1 + r2 * math.sin(a2)
y2 = y1 + r2 * math.cos(a2)

pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)
running = True
clock = pygame.time.Clock()
timer = 0
screen = pygame.display.set_mode((windowWidth, windowHeight))
preva1 = a1
preva2 = a2
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


    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    # print(a1 % math.pi)

    # plays a sound when crossing a certain point:
    # TODO: Append lists in crossing function.
    #       Wewrite if statement to be able to use the snare sound
    def crossing(angle, prevangle, drumsound, min, max, list):
        if angle > max and prevangle < min:
            drumsound.play()
            list.append(timer)
        if angle < min and prevangle > max:
            drumsound.play()
            list.append(timer)

# TODO: collision detection - maakgwneenbalaan. maak markdown bestanden

#checks if there is a kick or snare to be played
    crossing(a1, preva1, kicksound, 0.2, 3.0, kick)
    crossing(a2, preva2, hihatsound, 0.2, 3.0, hihat)
    crossing(x2, prevx2, snaresound, xZero, xZero, snare)


    pygame.display.flip()
#TODO: make clock.tick preciser
    clock.tick(60)
    #keeps track of the current moment in framerate
    timer = timer + 1
    #makes history of angles an x position
    preva1 = a1
    preva2 = a2
    prevx2 = x2

    if timer > time:
        running = False

pygame.quit()
print
print("kick: ", kick)
print("snare: ", snare)
print("hihat: ", hihat)

actualKick = []
actualSnare = []
actualHihat = []
offSetList = []

# print(kick[0])
firstHit = [kick[0], snare[0], hihat[0]]
firstHit.sort()

# removes the silent time before the sequence
for f in range(0, len(kick)):
    actualKick.append(kick[f] - firstHit[0])
for g in range(0, len(snare)):
    actualSnare.append(snare[g] - firstHit[0])
for h in range(0, len(hihat)):
    actualHihat.append(hihat[h] - firstHit[0])

pygame.quit()
print("actualkick: ", actualKick)
print("actualsnare: ", actualSnare)
print("actualhihat: ", actualHihat)

kickSnare = actualKick + actualSnare
kickSnare.sort()


# TODO: put creation of grid in function
for i in range(3, 23, 2):

    # defines the duration of one beat on the grid
    totalOffSet = 0
    beat = (time - firstHit[0])/i
    grid = []

    # makes a grid in an array
    for j in range(0, i):
        grid.append(beat * j)

    # calculates how much the kick deviates from the grid to later choose the smallest offset
    for drumhit in kickSnare:

        offSet = []
        for count in grid:
            #makes list of all offsets from one drumhit to every beat
            offSet.append(abs(drumhit - count))
        #chooses the smallest offset to calculate the total offset of one grid
        totalOffSet = totalOffSet + min(offSet)

    offSetList.append(totalOffSet)


print("totaloffsetlist to check best timesig: ", offSetList)
biasedOffSetList = []
for currentOffSet in offSetList:
    biasedOffSet = 130 - (150/(currentOffSet+1))
    biasedOffSetList.append(biasedOffSet)

print("biasedOffSetList to check best timesig: ", biasedOffSetList)

smallest = min(biasedOffSetList)
print("whooooooo:", smallest)
timeSig = biasedOffSetList.index(smallest) * 2 + 3
print("timesig = ", timeSig)

#TODO: make option for user to overwrite the timeSig

beatDur = time/timeSig
print(beatDur)

actualGrid = []
for l in range(0, timeSig):
    actualGrid.append(beatDur * l)
print("here come the warm girds: ", actualGrid)

def find_closest_num(number, grid):
    #absolute value of all offsets in a list
    absOffSets = []
    #value of all offsets in a list
    offSets = []
    #total difference between grid and drumpattern expressed in all offsets
    totalOffSet = 0
    #all differences between drumhit and grid in a list
    totalOffSetList = []
    #checks drumhits offset from grid and makes a list of offsets
    for count in grid:
        #calculates the offset
        offSet = number - count
        #makes list of offsets
        offSets.append(offSet)
        #makes list of absolute offsets
        absOffSets.append(abs(offSet))
        #minAbsOffSet is the smallest offset between beat and drumhit
        minAbsOffSet = min(absOffSets)
        #the following two lines are only useful to later define the best grid.
        totalOffSets = totalOffSet + minAbsOffSet
        totalOffSetList.append(totalOffSet)
    minOffSet = (offSets[absOffSets.index(minAbsOffSet)])
    closestBeat = grid[absOffSets.index(minAbsOffSet)]
    # smallestRelativeOffSet = offSets[absOffSets.index(minAbsOffSet)]
    # print(grid[offSet.index(min(offSet))])
    return closestBeat, minOffSet

for drumHit in kickSnare:
    closestbeat, relativeOffSet = find_closest_num(drumHit, grid)
    # print("beat: ", closestbeat)
    # print("offset: ", relativeOffSet)
# function to quantize a list
def quantizeList(list, gridList):
    quantizedList = []
    for hit in list:
        # find the closest beat:
        closestBeat, actualOffSet = find_closest_num(hit, gridList)
        print("this is the closest beat: ", closestBeat)
        quantizedList.append(closestBeat)
    return quantizedList

# using the function above to quantize the kick snare and hihat
quantizedKick = quantizeList(actualKick, actualGrid)
quantizedSnare = quantizeList(actualSnare, actualGrid)
quantizedHihat = quantizeList(actualHihat, actualGrid)

print("hey boss here is the quantized kick: ", quantizedKick)
print("hey boss here is the quantized snare: ", quantizedSnare)
print("hey boss here is the quantized hat: ", quantizedHihat)
