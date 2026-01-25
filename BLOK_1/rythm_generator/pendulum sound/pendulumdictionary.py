import pygame
import math
import time as t

#pygame stuff
pygame.init()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)


r1 = 180
r2 = 180
m1 = 0.1
m2 = 0.1
a1_v = 0
a2_v = 0
a1_a = 0
a2_a = 0
g = 1
running = True
clock = pygame.time.Clock()
teimr = 0
windowWidth = 800
windowHeight = 800
screen = pygame.display.set_mode((windowWidth, windowHeight))
# preva1 = a1
# preva2 = a2
# prevx2 = x2

pendulumDict = {
    'xZero': 0,
    'yZero': 0,
    'straaltje1': 180,
    'straaltje2': 180,
    'm1': 0.1,
    'm2': 0.1,
    'a1': 90,
    'a2': 0,
    'a1_v': 0,
    'a2_v': 0,
    'a1_a': 0,
    'a2_a': 0,
    'g': 1,
    'preva1': 'a1',
    'preva2': 'a2',
    'prevx2': 'x2',
    'prevX': '0',
    'prevY': '0',
    'prevA': '0'
}

xZero = windowWidth / 2
pendulumDict['xZero'] = xZero
yZero = windowHeight / 2 - 20
pendulumDict['yZero'] = yZero

#credits for all the math implementation of the pendulum to the coding train (https://thecodingtrain.com/challenges/93-double-pendulum)
correctAngle1Input = False
# default degrees1
degrees1 = 90
screen = pygame.display.set_mode((windowWidth, windowHeight))


while (not correctAngle1Input):
    user_degrees1 = input("enter angle in degrees (leave empty for default 90)")

    # check if we 'received' an empty string
    if not user_degrees1:
        # empty string --> use default
        correctAngle1Input = True
    else:
        try:
            degrees1 = float(user_degrees1)
            if degrees1 >= 0 and degrees1 <= 360:
                correctAngle1Input = True
            else:
                degrees1 = 90
                print("Incorrect input - please enter an angle in degrees 0 to 360 (or enter nothing - default angle 90 degrees)")
        except:
            print("Incorrect input - please enter an angle in degrees (or enter nothing - default angle 90 degrees)")

a1 = degrees1 * math.pi / 180
correctAngle1Input = False
# default degrees2
degrees2 = 90

while (not correctAngle1Input):
    user_degrees2 = input("enter angle in degrees (leave empty for default 90)")

    # check if we 'received' an empty string
    if not user_degrees2:
        # empty string --> use default
        correctAngle1Input = True
    else:
        try:
            degrees2 = float(user_degrees2)
            if degrees2 >= 0 and degrees2 <= 360:
                correctAngle1Input = True
            else:
                degrees2 = 90
                print("Incorrect input - please enter an angle in degrees 0 to 360 (or enter nothing - default angle 90 degrees)")
        except:
            print("Incorrect input - please enter an angle in degrees (or enter nothing - default angle 90 degrees)")
a2 = degrees2 * math.pi / 180
#TODO: take modulo of degrees so if degrees > 360 the pendulum will still trigger the if else statements
# teim_seconds = float(input("how long do you want the double pendulum to run in seconds"))
teim_seconds = 10
teim = teim_seconds
#lists for the drums
kick = []
snare = []
hihat = []
drums = []
velocityList = []

#TODO: make stuff only camelcase
running = True
clock = pygame.time.Clock()
teimr = 0
kitQuestion = 'sup homie wahat sample pack do you want'
kitOptions = ['de ãtechre', 'dark vibes dud']

def retrieveUserInput(question, options):
    if(not str(question)):
        raise TypeError(
            'question needs to be a string')
    print(question)
    for i, option in enumerate(options):
        print(i + 1, ':', option)
    print('leave empty for default option 1 dud')
    return input()

def validateIntRange(value, rangeLow, rangeHigh):
    try:
        intValue = int(value)
        if (intValue >= rangeLow and intValue <= rangeHigh):
            return True
    except:
        return False

    return False

def retrieveUserOption(question, options):
    selectedOption = 1
    correctInput = False
    while(not correctInput):
        userInput = retrieveUserInput(question, options)
        if(validateIntRange(userInput, 1, len(options))):
            selectedOption = int(userInput)
            correctInput = True

        elif(not userInput):
            correctInput = True
        else:
            print('incorrect input, try again of fuck off dud.\n\n')

    selectedOption -= 1
    return options[selectedOption]

def get_currentFrameTime(drums):
    return drums["currentFrameTime"]

def pendulumDraw(pendulumDict):
    r1 = float(pendulumDict.get('straaltje1'))
    r2 = float(pendulumDict.get('straaltje2'))
    a1 = float(pendulumDict.get('a1'))
    a2 = float(pendulumDict.get('a2'))
    xZero = int(pendulumDict.get('xZero'))
    xZero = int(pendulumDict.get('xZero'))

    screen.fill((10, 10, 10))
    x1 = r1 * math.sin(a1) + xZero
    y1 = r1 * math.cos(a1) + yZero
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
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
    r1 = float(pendulumDict.get('straaltje1'))
    r2 = float(pendulumDict.get('straaltje2'))
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
    # preva1 = a1
    # preva2 = a2
    # prevx2 = x2
    pendulumDict['a1_v'] = a1_v
    pendulumDict['a2_v'] = a2_v
    pendulumDict['a1_a'] = a1_a
    pendulumDict['a2_a'] = a2_a
    pendulumDict['a1'] = a1
    pendulumDict['a2'] = a2
    return pendulumDict

def crossing(angle, prevangle, drumsound, min, max, list, angleVelocity):
    if angle > max and prevangle < min:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 50
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(teimr)
        print("velocity: ", noteVelocity)
    if angle < min and prevangle > max:
        drumsound.play()
        noteVelocity = abs(angleVelocity * 500) + 50
        if noteVelocity > 127:
            noteVelocity = 127
        velocityList.append(noteVelocity)
        list.append(teimr)
        print("velocity: ", noteVelocity)

def quantizeList(list, gridList):
    quantizedList = []
    for hit in list:
        # find the closest beat:
        closestBeat, actualOffSet = find_closest_num(hit, gridList)
        # print("this is the closest beat: ", closestBeat)
        quantizedList.append(closestBeat)
    return quantizedList

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
    return closestBeat, minOffSet

def handle_note_event(sample, velocity):
    print(sample)
    sample.set_volume(velocity / 127.0)
    sample.play()

selectedKit = retrieveUserOption(kitQuestion, kitOptions)

if selectedKit == "de ãtechre":
    kicksound = pygame.mixer.Sound('kick.mp3')
    snaresound = pygame.mixer.Sound('snare.mp3')
    hihatsound = pygame.mixer.Sound('hihat.mp3')

else:
    kicksound = pygame.mixer.Sound('dark_kick.mp3')
    snaresound = pygame.mixer.Sound('dark_snare.mp3')
    hihatsound = pygame.mixer.Sound('dark_hat.mp3')

print('you ave chosen.... ', selectedKit)

# print(pendulumDict)


running = True
while running == True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    klokje = clock.tick(60)
    timer = timer + (klokje / 1000)

    screen.fill((10, 10, 10))
    # line3 = pygame.draw.line(screen, (200, 0, 150), (0, 100), (yes, no))
    pendulumDraw(pendulumDict)
    calculatePendulumAngle(pendulumDict, klokje)
    pygame.display.flip()

pygame.quit()


# print
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
#       make sure the grid doesnt cut off the last note

for i in range(3, 23):
    # defines the duration of one beat on the grid
    totalOffSet = 0
    beat = (teim - firstHit[0])/(i+1)
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

# TODO: make function to bias offset
for currentOffSet in offSetList:
    biasedOffSet = 130 - (150/(currentOffSet+1))
    biasedOffSetList.append(biasedOffSet)

# print("biasedOffSetList to check best teimsig: ", biasedOffSetList)

smallest = min(biasedOffSetList)
# print("whooooooo:", smallest)
teimSig = biasedOffSetList.index(smallest) * 2 + 3
print("teimsig = ", teimSig)

#TODO: make option for user to overwrite the teimSig

beatDur = teim/(teimSig+1)
# print(beatDur)



actualGrid = []
for l in range(0, teimSig):
    actualGrid.append(beatDur * l)
# print("here come the warm girds: ", actualGrid)

for drumHit in kickSnare:
    closestbeat, relativeOffSet = find_closest_num(drumHit, grid)
    # print("beat: ", closestbeat)
    # print("offset: ", relativeOffSet)
# function to quantize a list

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
#makes list with dictionaries of samplesound and timestamp
lists_to_dictionary_list(quantizedKick, kicksound)
lists_to_dictionary_list(quantizedSnare, snaresound)
lists_to_dictionary_list(quantizedHihat, hihatsound)


drums.sort(key=get_currentFrameTime)

for drum in drums:
    # print(drum)
    drum['velocity'] = velocityList[drums.index(drum)]


onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
pygame.init()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)

drumscopy = drums

#playing stuff lolz

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
