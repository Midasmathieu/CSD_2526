# removes silence
def removeSilence(sequence, silence):
    index = 0
    for note in sequence:
        noteMinSilence = note - silence
        sequence[index] = noteMinSilence
        index = index + 1
        return sequence
# finds (and then removes) empty time between the start of the
# pendulum simulation and the first drumhit
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

# calculates the beatduration of the selected timesignature if the runtime is one measure
def retrieveBeatsInTimesig(signatureList, signature):
    index = signatureList.index(signature)
    beatsInTimeSig = index * 2 + 5
    return beatsInTimeSig

# creates a grid fitting the timesignature in the time the pendulum produces sound
def createGrid(bar, beatsInTimeSig):
    beatDur = bar / beatsInTimeSig
    grid = []
    for count in range(beatsInTimeSig):
        grid.append(count * beatDur)
    # print(grid)
    return grid, beatDur

# function that finds the closest number in a list
# found this here no clue how it works.. https://www.geeksforgeeks.org/python/python-find-closest-number-to-k-in-given-list/
def closest(lst, K):
    closestBeat = lst[min(range(len(lst)), key = lambda i: abs(lst[i]-K))]
    return closestBeat

# quantizes list hard to nearest beats on the grid
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

# calculates the timestamps to 'beatstamps'
def timeSigToBeats(timeList, beatDur):
    beatsList = []
    for time in timeList:
        beat = time / beatDur
        beatsList.append(beat)
    # print('this is the beatlist', beatsList)
    return beatsList

# calculates the 'beatstamps' to timestamps in a bpm
def beatsToTimeStamp(BPM, sequence):
    beatDur = 60 / BPM
    # print('beatDur: ', beatDur)
    timeStampList = []
    for hit in sequence:
        timeStamp = hit * beatDur
        timeStampList.append(timeStamp)
    return timeStampList

# puts all the drumlists in a dictionary list
def listsToDictionary(list, sampleName, drums):
    for number in list:
        drums.append({
            'sound': sampleName,
            'currentFrameTime': number
    })

# gets the current frametime (no shit!) to know when the next sample needs to be played
def getCurrentFrameTime(drums):
    return drums["currentFrameTime"]


# this is a very janky calculation of how long one measure should take, it is
# based on "logic" and a whole lot of trial and error half an hour before the presentation
def calculateTimeDur(BPM, timeSig):
    beatDur = 60 / BPM
    # print('timesig: ', timeSig)
    sequenceDur = ((timeSig - 2) * beatDur) / 2
    doubleSequenceDur = sequenceDur * 2
    tripleSequenceDur = sequenceDur * 3
    return sequenceDur, doubleSequenceDur, tripleSequenceDur

# make a list that adds a time duration to each timestamp to make a second, third etc measure
def makePlayBackList(list, timeDur):
    secondList = []
    for hit in list:
        secondListHit = hit + timeDur
        secondList.append(secondListHit)
    return secondList

# removes the duplicates so a sample is not triggered twice at the same time
def removeDuplicates(list):
    newList = []
    for number in list:
        if number not in newList:
            newList.append(number)
    return newList
