import pygame
import math
import time as t
import pendulumFunctions as pendulum
import UIFunctions

def removeSilence(sequence, silence):
    index = 0
    for note in sequence:
        noteMinSilence = note - silence
        sequence[index] = noteMinSilence
        index = index + 1
        return sequence


def findSilence(kicks, snares, hihats, duration):
    firstHitList = [kicks[0], snares[0], hihats[0]]
    firstHitList.sort()
    firstHit = firstHitList[0]
    # removes the silent teim before the sequence
    removeSilence(kicks, firstHit)
    removeSilence(snares, firstHit)
    removeSilence(hihats, firstHit)
    measureDur = duration - firstHit
    return measureDur


def retrieveBeatsInTimesig(signatureList, signature):
    index = signatureList.index(signature)
    beatsInTimeSig = index * 2 + 5
    return beatsInTimeSig

def createGrid(bar, beatsInTimeSig):
    beatDur = bar / beatsInTimeSig
    grid = []
    for count in range(beatsInTimeSig):
        grid.append(count * beatDur)
    # print(grid)
    return grid, beatDur

# found this here no clue how it works.. https://www.geeksforgeeks.org/python/python-find-closest-number-to-k-in-given-list/

def closest(lst, K):
    closestBeat = lst[min(range(len(lst)), key = lambda i: abs(lst[i]-K))]
    return closestBeat

def quantizeList(list, gridList):
    quantizedList = []
    # print('gridlist: ', gridList)
    for hit in list:
        # find the closest beat:
        quantizedHit = closest(gridList, hit)
        # print('hit: ', hit, 'closestbeat: ', closestBeat, 'offSet: ', offSet, 'quantizedHit: ', quantizedHit)
        # print("this is the closest beat: ", closestBeat)
        quantizedList.append(quantizedHit)
    return quantizedList

def timeSigToBeats(timeList, beatDur):
    beatsList = []
    for time in timeList:
        beat = time / beatDur
        beatsList.append(beat)
    # print('this is the beatlist', beatsList)
    return beatsList

def beatsToTimeStamp(BPM, sequence):
    beatDur = 60 / BPM
    # print('beatDur: ', beatDur)
    timeStampList = []
    for hit in sequence:
        timeStamp = hit * beatDur
        timeStampList.append(timeStamp)
    return timeStampList

def listsToDictionary(list, sampleName, drums):
    for number in list:
        drums.append({
            'sound': sampleName,
            'currentFrameTime': number
    })

def getCurrentFrameTime(drums):
    return drums["currentFrameTime"]


def calculateTimeDur(BPM, timeSig):
    beatDur = 60 / BPM
    # print('timesig: ', timeSig)
    sequenceDur = ((timeSig - 2) * beatDur) / 2
    doubleSequenceDur = sequenceDur * 2
    tripleSequenceDur = sequenceDur * 3
    return sequenceDur, doubleSequenceDur, tripleSequenceDur

#make the playbacklist first in normal lists

def makePlayBackList(list, timeDur):
    secondList = []
    for hit in list:
        secondListHit = hit + timeDur
        secondList.append(secondListHit)
    return secondList

def removeDuplicates(list):
    newList = []
    for number in list:
        if number not in newList:
            newList.append(number)
    return newList

pygame.init()
windowWidth = 800
windowHeight = 800
screen = pygame.display.set_mode((windowWidth, windowHeight))
clock = pygame.time.Clock()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)
timer = 0

pendulumDict = {
    'xZero': 0,
    'yZero': 0,
    'r1': 180,
    'r2': 180,
    'm1': 1,
    'm2': 1,
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
yZero = (windowHeight / 5) * 2
pendulumDict['yZero'] = yZero


kicks = []
snares = []
hihats = []
velocityList = []

generalError = 'oh oh error, try again...'
pendulumQuestion1 = 'How many degrees do you want to set pendulum 1? \n 0 to 360 degrees. (default = 90 degrees) \n'
pendulumQuestion2 = 'How many degrees do you want to set pendulum 2? \n 0 to 360 degrees. (default = 90 degrees)\n'

anglePendulum1 = UIFunctions.retrieveUserInput(0, 360, 90, pendulumQuestion1, generalError, ' degrees it is!\n')
anglePendulum2 = UIFunctions.retrieveUserInput(0, 360, 90, pendulumQuestion2, generalError, ' degrees it is!\n')
a1 = math.radians(anglePendulum1)
a2 = math.radians(anglePendulum2)


pendulumDict['a1'] = a1
pendulumDict['a2'] = a2
pendulumDict['prevA1'] = (pendulumDict.get('a1'))
pendulumDict['prevA2'] = (pendulumDict.get('a2'))

pendulum.calculatePendulumPos(pendulumDict)
pendulumDict['prevX2'] = (pendulumDict.get('x2'))

kitQuestion = 'what sample pack do you want to select?'
kitOptions = ['de ãtechre', 'dark vibes dud\n']
selectedKit = UIFunctions.retrieveUserOption(kitQuestion, kitOptions)

if selectedKit == "de ãtechre":
    kickSound = pygame.mixer.Sound('kick.mp3')
    snareSound = pygame.mixer.Sound('snare.mp3')
    hihatSound = pygame.mixer.Sound('hihat.mp3')

else:
    kickSound = pygame.mixer.Sound('dark_kick.mp3')
    snareSound = pygame.mixer.Sound('dark_snare.mp3')
    hihatSound = pygame.mixer.Sound('dark_hat.mp3')

timeQuestion = 'How long do you want the pendulum to swing in seconds?\n 2 to 7 seconds. (default = 4 seconds)\n'
secondsRunning = UIFunctions.retrieveUserInput(2, 7, 4, timeQuestion, generalError, ' seconds it is!\n')

#GAMELOOP!
timer = 0
klokje = 0
running = True
while running == True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    klokje = clock.tick(60)
    if klokje > 50:
        klokje = 0

    timer = timer + (klokje / 1000)

    if timer > secondsRunning:
        running = False

    # if timer > secondsRunning:
    #     running = False

    screen.fill((10, 10, 10))
    # line3 = pygame.draw.line(screen, (200, 0, 150), (0, 100), (yes, no))
    pendulum.calculatePendulumPos(pendulumDict)
    pendulum.pendulumDraw(pendulumDict, screen)
    pendulum.calculatePendulumAngle(pendulumDict, klokje)
    pendulum.crossing(pendulumDict.get('a1'), pendulumDict.get('prevA1'), kickSound, 0.5, 2.6, kicks, pendulumDict.get('a1_v'), velocityList, timer)
    pendulum.crossing(pendulumDict.get('a2'), pendulumDict.get('prevA2'), hihatSound, 0.5, 2.6, hihats, pendulumDict.get('a2_v'), velocityList, timer)
    pendulum.crossing(pendulumDict.get('x2'), pendulumDict.get('prevX2'), snareSound, pendulumDict.get('xZero'), pendulumDict.get('xZero'), snares, pendulumDict.get('a2_v'), velocityList, timer)
    pendulum.pendulumHistory(pendulumDict)
t.sleep(0.50)
pygame.quit()

signatureQuestion = "what time signature do you want to quantize that to?"
signatureOptions = ['5/4', '7/4', '9/4', '11/4', '13/4 because you are a little pretentious fucking guy...\n']
selectedSignature = UIFunctions.retrieveUserOption(signatureQuestion, signatureOptions)
BPMQuestion = 'How fast do you want to play it back? Enter BPM... (default = 120)\n'
selectedBPM = UIFunctions.retrieveUserInput(60, 220, 120, BPMQuestion, generalError, 'Beats per minute it is!\n')



# def makePlayBackList(list, timeDur):
#     firstList = copy.deepcopy(list, 1)
#     print('playBackList1: ', firstList, '\n\n')
#     listLooped = copy.deepcopy(list, 2)
#     for hit in listLooped:
#         print('hitframetime: ', hit['currentFrameTime'])
#         hit['currentFrameTime'] = hit['currentFrameTime'] + timeDur
#         print('hitframetime2: ', hit['currentFrameTime'])
#     print('playBackList2: ', firstList, '\n\n')
#     playBackList = firstList + listLooped
#     print('listLooped: ', listLooped, '\n\n')
#     print('finallist: ', playBackList, '\n\n')
#     return playBackList


measure = findSilence(kicks, snares, hihats, secondsRunning)
beatsInTimeSig = retrieveBeatsInTimesig(signatureOptions, selectedSignature)
grid, beatDur = createGrid(measure, beatsInTimeSig)
# print('grid: ', grid)
quantizedKicks = quantizeList(kicks, grid)
quantizedSnares = quantizeList(snares, grid)
quantizedHihats = quantizeList(hihats, grid)
kickBeats = timeSigToBeats(quantizedKicks, beatDur)
snareBeats = timeSigToBeats(quantizedSnares, beatDur)
hihatBeats = timeSigToBeats(quantizedHihats, beatDur)
kickTimeStamps = beatsToTimeStamp(selectedBPM, quantizedKicks)
snareTimeStamps = beatsToTimeStamp(selectedBPM, quantizedSnares)
hihatTimeStamps = beatsToTimeStamp(selectedBPM, quantizedHihats)
sequenceDur, doubleSequenceDur, tripleSequenceDur = calculateTimeDur(selectedBPM, beatsInTimeSig)
# print('sequencedur:    ', sequenceDur)
secondKickTimeStamps = makePlayBackList(kickTimeStamps, sequenceDur)
thirdKickTimeStamps = makePlayBackList(kickTimeStamps, doubleSequenceDur)
fourthKickTimeStamps = makePlayBackList(kickTimeStamps, tripleSequenceDur)

secondSnareTimeStamps = makePlayBackList(snareTimeStamps, sequenceDur)
thirdSnareTimeStamps = makePlayBackList(snareTimeStamps, doubleSequenceDur)
fourthSnareTimeStamps = makePlayBackList(snareTimeStamps, tripleSequenceDur)

secondHihatTimeStamps = makePlayBackList(hihatTimeStamps, sequenceDur)
thirdHihatTimeStamps = makePlayBackList(hihatTimeStamps, doubleSequenceDur)
fourthHihatTimeStamps = makePlayBackList(hihatTimeStamps, tripleSequenceDur)


twoKickTimeStamps = kickTimeStamps + secondKickTimeStamps + thirdKickTimeStamps + fourthKickTimeStamps
twoSnareTimeStamps = snareTimeStamps + secondSnareTimeStamps + thirdSnareTimeStamps + fourthSnareTimeStamps
twoHihatTimeStamps = hihatTimeStamps + secondHihatTimeStamps + thirdHihatTimeStamps + fourthHihatTimeStamps

finalKickTimeStamps = removeDuplicates(twoKickTimeStamps)
finalSnareTimeStamps = removeDuplicates(twoSnareTimeStamps)
finalHihatTimeStamps = removeDuplicates(twoHihatTimeStamps)


# print('sequenceDur: ', sequenceDur)

drums = []

# listsToDictionary(kickTimeStamps, kickSound, drums)
# listsToDictionary(snareTimeStamps, snareSound, drums)
# listsToDictionary(hihatTimeStamps, hihatSound, drums)
listsToDictionary(finalKickTimeStamps, kickSound, drums)
listsToDictionary(finalSnareTimeStamps, snareSound, drums)
listsToDictionary(finalHihatTimeStamps, hihatSound, drums)


# print('drums: ', drums)
# velocityList2 = velocityList.copy()
# totalVelocityList = velocityList + velocityList2
# print('velocitylist2: ', totalVelocityList)
#
# for drum in drums:
#     # print(drum)
#     drum['velocity'] = velocityList2[drums.index(drum)]


# print('drums2: ', drums2, '\n\n')
#
# secondKickTimeStamps = makePlayBackList(kickTimeStamps, sequenceDur)
# secondSnareTimeStamps = makePlayBackList(snareTimeStamps, sequenceDur)
# secondHihatTimeStamps = makePlayBackList(hihatTimeStamps, sequenceDur)

drums.sort(key=getCurrentFrameTime)

playAgainQuestion = "Do you want to play that again but quantized?"
playAgainOptions = ['Yes', 'No']
oneMoreTime = UIFunctions.retrieveUserOption(playAgainQuestion, playAgainOptions)

# oneMoreTime = input("hey booosss do you want to hear that #oneMoreTime??... yes or no boosssss...")
pygame.init()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)

drumscopy = drums

# TODO: make duplicates of drums with the total length of the loop added once twice -
#  or thrice to the timestamps, then add the lists and play them.

#also put the functions for the quantization in a seperate bestand and put useful comments everywhere,
#  GOOD LUCK :))) DON'T FUCKING GET DESTRACTED HAHAHAHAHAHAHAHAHAH

#playing stuff lolz

if oneMoreTime == 'Yes':
    running = True
    sampleSound = drumscopy[0].get('sound')
    # sampleVelocity = drumscopy[0].get('velocity')
    ts = drumscopy.pop(0).get('currentFrameTime')
    pendulum.playNote(sampleSound, 127)
    # handle_note_event(sampleSound, sampleVelocity)
else:
    running = False

time_zero = t.time()

while running == True:

    currentTime = t.time() - time_zero
    # print('time: ', currentTime)
    if (currentTime > ts):
        pendulum.playNote(sampleSound, 127)
        # print('note: ', currentTime)
        # handle_note_event(sampleSound, sampleVelocity)
        if drumscopy:
            # ts = drums[0].get('currentFrameTime')
            sampleSound = drumscopy[0].get('sound')
            # sampleVelocity = drumscopy[0].get('velocity')
            ts = drumscopy.pop(0).get('currentFrameTime')
            # print(drums[0].get('currentFrameTime'))
        else:
            # print(drums)
            break

t.sleep(1.0)
print('I hope that was irregular enough for you')



# print('kicks: ', kicks)
# print('sners: ', snares)
# print('hihats: ', hihats)
# print('quantizedKicks: ', quantizedKicks)
# print('kickbeats: ', kickBeats)
# print('timestampKicks:', kickTimeStamps)
# print('timestampSnares:', snareTimeStamps)
# print('timestampHats:', hihatTimeStamps)
