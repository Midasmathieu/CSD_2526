import pygame
import math
import time as t
import pendulumFunctions as pendulum
import UIFunctions
import quantizeFunctions

# took a lot of pygame info (mainly for the animation) from this video: https://www.youtube.com/watch?v=blLLtdv4tvo
pygame.init()
windowWidth = 800
windowHeight = 800
screen = pygame.display.set_mode((windowWidth, windowHeight))
clock = pygame.time.Clock()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)
timer = 0

# dictionary with traits of the pendulum, I choose to keep the names relatively 'natuurkundig'
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

# make lists to append timestamps
# (includes velocity list wich is not used due to bad planning on my part)
kicks = []
snares = []
hihats = []
velocityList = []

# set the angle of the two pendulums
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

# cand make shure x2 = prevX2 so when the simulation starts no snare is played
pendulum.calculatePendulumPos(pendulumDict)
pendulumDict['prevX2'] = (pendulumDict.get('x2'))

# select sample pack and duration that the simulation runs
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

#GAMELOOP! (the pendulum is being simulated and animated in this while loop)
timer = 0
klokje = 0
running = True
while running == True:
# makes shure you can quit pygame by pressing the x button in the corner
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

# keeps time
    klokje = clock.tick(60)
    if klokje > 50:
        klokje = 0
    timer = timer + (klokje / 1000)

    if timer > secondsRunning:
        running = False

# calculates and draws the pendulum
    screen.fill((10, 10, 10))
    pendulum.calculatePendulumPos(pendulumDict)
    pendulum.pendulumDraw(pendulumDict, screen)
    pendulum.calculatePendulumAngle(pendulumDict, klokje)
# crossing appends the moment in time to a list if a drum gets triggered
    pendulum.crossing(pendulumDict.get('a1'), pendulumDict.get('prevA1'), kickSound, 0.5, 2.6, kicks, pendulumDict.get('a1_v'), velocityList, timer)
    pendulum.crossing(pendulumDict.get('a2'), pendulumDict.get('prevA2'), hihatSound, 0.5, 2.6, hihats, pendulumDict.get('a2_v'), velocityList, timer)
    pendulum.crossing(pendulumDict.get('x2'), pendulumDict.get('prevX2'), snareSound, pendulumDict.get('xZero'), pendulumDict.get('xZero'), snares, pendulumDict.get('a2_v'), velocityList, timer)
    pendulum.pendulumHistory(pendulumDict)
t.sleep(0.50)
pygame.quit()

# more UI: bpm & timesig
signatureQuestion = "what time signature do you want to quantize that to?"
signatureOptions = ['5/4', '7/4', '9/4', '11/4', '13/4 because you are a little pretentious fucking guy...\n']
selectedSignature = UIFunctions.retrieveUserOption(signatureQuestion, signatureOptions)
BPMQuestion = 'How fast do you want to play it back? Enter BPM... (default = 120)\n'
selectedBPM = UIFunctions.retrieveUserInput(60, 220, 120, BPMQuestion, generalError, 'Beats per minute it is!\n')

# prepairs some numbers for quantization
measure = quantizeFunctions.findSilence(kicks, snares, hihats, secondsRunning)
beatsInTimeSig = quantizeFunctions.retrieveBeatsInTimesig(signatureOptions, selectedSignature)
grid, beatDur = quantizeFunctions.createGrid(measure, beatsInTimeSig)

# quantizes the lists
quantizedKicks = quantizeFunctions.quantizeList(kicks, grid)
quantizedSnares = quantizeFunctions.quantizeList(snares, grid)
quantizedHihats = quantizeFunctions.quantizeList(hihats, grid)

# make lists in 'beat stamps' (so first beat second beat third beat etc)
kickBeats = quantizeFunctions.timeSigToBeats(quantizedKicks, beatDur)
snareBeats = quantizeFunctions.timeSigToBeats(quantizedSnares, beatDur)
hihatBeats = quantizeFunctions.timeSigToBeats(quantizedHihats, beatDur)

# makes timestamps for the beats with a given bpm
kickTimeStamps = quantizeFunctions.beatsToTimeStamp(selectedBPM, quantizedKicks)
snareTimeStamps = quantizeFunctions.beatsToTimeStamp(selectedBPM, quantizedSnares)
hihatTimeStamps = quantizeFunctions.beatsToTimeStamp(selectedBPM, quantizedHihats)

# calculates time duration of one measure, two measures and three measures
sequenceDur, doubleSequenceDur, tripleSequenceDur = quantizeFunctions.calculateTimeDur(selectedBPM, beatsInTimeSig)

# ads time duration of one/two/three measures to lists
secondKickTimeStamps = quantizeFunctions.makePlayBackList(kickTimeStamps, sequenceDur)
thirdKickTimeStamps = quantizeFunctions.makePlayBackList(kickTimeStamps, doubleSequenceDur)
fourthKickTimeStamps = quantizeFunctions.makePlayBackList(kickTimeStamps, tripleSequenceDur)

secondSnareTimeStamps = quantizeFunctions.makePlayBackList(snareTimeStamps, sequenceDur)
thirdSnareTimeStamps = quantizeFunctions.makePlayBackList(snareTimeStamps, doubleSequenceDur)
fourthSnareTimeStamps = quantizeFunctions.makePlayBackList(snareTimeStamps, tripleSequenceDur)

secondHihatTimeStamps = quantizeFunctions.makePlayBackList(hihatTimeStamps, sequenceDur)
thirdHihatTimeStamps = quantizeFunctions.makePlayBackList(hihatTimeStamps, doubleSequenceDur)
fourthHihatTimeStamps = quantizeFunctions.makePlayBackList(hihatTimeStamps, tripleSequenceDur)

# adds lists to make four measures
fourKickTimeStamps = kickTimeStamps + secondKickTimeStamps + thirdKickTimeStamps + fourthKickTimeStamps
fourSnareTimeStamps = snareTimeStamps + secondSnareTimeStamps + thirdSnareTimeStamps + fourthSnareTimeStamps
fourHihatTimeStamps = hihatTimeStamps + secondHihatTimeStamps + thirdHihatTimeStamps + fourthHihatTimeStamps

# removes duplicates
finalKickTimeStamps = quantizeFunctions.removeDuplicates(fourKickTimeStamps)
finalSnareTimeStamps = quantizeFunctions.removeDuplicates(fourSnareTimeStamps)
finalHihatTimeStamps = quantizeFunctions.removeDuplicates(fourHihatTimeStamps)

# makes dictionary list
drums = []
quantizeFunctions.listsToDictionary(finalKickTimeStamps, kickSound, drums)
quantizeFunctions.listsToDictionary(finalSnareTimeStamps, snareSound, drums)
quantizeFunctions.listsToDictionary(finalHihatTimeStamps, hihatSound, drums)

# sorts drums
drums.sort(key=quantizeFunctions.getCurrentFrameTime)

# UI question for playback
playAgainQuestion = "Do you want to play that again but quantized?"
playAgainOptions = ['Yes', 'No']
oneMoreTime = UIFunctions.retrieveUserOption(playAgainQuestion, playAgainOptions)

# starts pygame again to play notes
pygame.init()
pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.set_num_channels(16)

# starts playback
if oneMoreTime == 'Yes':
    running = True
    sampleSound = drums[0].get('sound')
    ts = drums.pop(0).get('currentFrameTime')
    pendulum.playNote(sampleSound, 127)
else:
    running = False

time_zero = t.time()

# playback while loop
while running == True:
    currentTime = t.time() - time_zero
    if (currentTime > ts):
        pendulum.playNote(sampleSound, 127)
        if drums:
            sampleSound = drums[0].get('sound')
            ts = drums.pop(0).get('currentFrameTime')
        else:
            break

t.sleep(1.0)
print('I hope that was irregular enough for you')
