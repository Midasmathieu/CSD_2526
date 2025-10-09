import pygame
import math
import time as t

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
teim_seconds = float(input("how long do you want the double pendulum to run in seconds"))
teim = teim_seconds

kick = []
snare = []
hihat = []
drums = []
velocityList = []

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
teimr = 0
screen = pygame.display.set_mode((windowWidth, windowHeight))
preva1 = a1
preva2 = a2
prevx2 = x2
kicksound = pygame.mixer.Sound('kick.mp3')
snaresound = pygame.mixer.Sound('snare.mp3')
hihatsound = pygame.mixer.Sound('hihat.mp3')

def get_currentFrameTime(drums):
    return drums["currentFrameTime"]

def crossing(angle, prevangle, drumsound, min, max, list, angleVelocity):
    if angle > max and prevangle < min:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 30
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(teimr)
        print("velocity: ", noteVelocity)
    if angle < min and prevangle > max:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 30
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(teimr)
        print("velocity: ", noteVelocity)

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


# TODO: collision detection - maakgwneenbalaan. maak markdown bestanden

#checks if there is a kick or snare to be played
    crossing(a1, preva1, kicksound, 0.2, 3.0, kick, a1_v)
    crossing(a2, preva2, hihatsound, 0.2, 3.0, hihat, a2_v)
    crossing(x2, prevx2, snaresound, xZero, xZero, snare, a2_v)


    pygame.display.flip()
#TODO: make clock.tick preciser
    clock.tick(60)
    #keeps track of the current moment in framerate
    teimr = teimr + 1/60
    # print(teimr)
    #makes history of angles an x position
    preva1 = a1
    preva2 = a2
    prevx2 = x2

    if teimr > teim:
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

# removes the silent teim before the sequence
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
    beat = (teim - firstHit[0])/i
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


# print("totaloffsetlist to check best teimsig: ", offSetList)
biasedOffSetList = []
for currentOffSet in offSetList:
    biasedOffSet = 130 - (150/(currentOffSet+1))
    biasedOffSetList.append(biasedOffSet)

# print("biasedOffSetList to check best teimsig: ", biasedOffSetList)

smallest = min(biasedOffSetList)
# print("whooooooo:", smallest)
teimSig = biasedOffSetList.index(smallest) * 2 + 3
print("teimsig = ", teimSig)

#TODO: make option for user to overwrite the teimSig

beatDur = teim/teimSig
# print(beatDur)

actualGrid = []
for l in range(0, teimSig):
    actualGrid.append(beatDur * l)
# print("here come the warm girds: ", actualGrid)

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
        # print("this is the closest beat: ", closestBeat)
        quantizedList.append(closestBeat)
    return quantizedList

# using the function above to quantize the kick snare and hihat
quantizedKick = quantizeList(actualKick, actualGrid)
quantizedSnare = quantizeList(actualSnare, actualGrid)
quantizedHihat = quantizeList(actualHihat, actualGrid)

def lists_to_dictionary_list(list, sampleName):
    for number in list:
        drums.append({
            'sound': sampleName,
            'currentFrameTime': number
    })


lists_to_dictionary_list(quantizedKick, kicksound)
lists_to_dictionary_list(quantizedSnare, snaresound)
lists_to_dictionary_list(quantizedHihat, hihatsound)



print("--- drums List ---")
# for drum in drums:
    # print(drum)

drums.sort(key=get_currentFrameTime)

print("--- drums List sorted by currentFrameTime ---")
for drum in drums:
    print(drum)

for drum in drums:
    # print(drum)
    drum['velocity'] = velocityList[drums.index(drum)]

print("--- drums List with velocity added ---")
for drum in drums:
    print(drum)

def handle_note_event(sample, velocity):
    print(sample)
    sample.set_volume(velocity / 127.0)
    sample.play()

# for i in range(0, len(drums)):
#     print(drums[i].get('sound'))


onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
pygame.init()

drumscopy = drums

if onemoretime == "yes":
    running = True
    sampleSound = drumscopy[0].get('sound')
    sampleVelocity = drumscopy[0].get('velocity')
    ts = drumscopy.pop(0).get('currentFrameTime')
    handle_note_event(sampleSound, sampleVelocity)
else:
    running = False

time_zero = t.time()

while running == True:
    currentTime = t.time() - time_zero
    if (currentTime > ts):
        handle_note_event(sampleSound, sampleVelocity)
        if drumscopy:
            # ts = drums[0].get('currentFrameTime')
            sampleSound = drumscopy[0].get('sound')
            sampleVelocity = drumscopy[0].get('velocity')
            ts = drumscopy.pop(0).get('currentFrameTime')
            # print(drums[0].get('currentFrameTime'))
        else:
            print(drums)
            break


t.sleep(0.001)
