
#
kick = []
snare = []
hihat = []
quantizedKick = []
quantizedSnare = []
quantizedHihat = []
milisec = 0

    degrees1 = float(input("where do you want pendulum1 to start in degrees?: "))
    start1 = degrees1 * math.pi / 180 / math.pi
    degrees2 = float(input("where do you want pendulum2 to start in degrees?: "))
    start2 = degrees1 * math.pi / 180 / math.pi
    time = input("how long do you want the double pendulum to run in miliseconds?")

function doublependulum(a1, a2, milisec){
    #r is the length of the pendula
    r1 = 180
    r2 = 180
    #m is the mass of the pendula
    m1 = 1
    m2 = 1
    #a is the angle of the pendula
    a1 = 2
    a2 = 2
    #a_v is the velocity of the angles
    a1_v = 0
    a2_v = 0
    #a_a is the acceleration of the angles
    a1_a = 0
    a2_a = 0
    #g is the gravity
    g = 10
    #lagrangian formula simulates movement of the pendulum using the earlier stated
    # intergers by giving the acceleration in radius
    a1_a = Lagrangian formula pendulum1;
    a1_a = Langangian formula pendulum2;
    #calculate the velocity and the new angle, return angles
    a1_v = a1_v + a1_a * milisec
    a1 = a1 + a1_v
    a2_v = a2_v + a2_a * milisec
    a2 = a2 + a2_v
    return a1, a2
    #calculate the xy positions and return them
    x1 = r1 * math.sin(a1)
    y1 = r1 * math.cos(a1)
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    return x1, y1, x2, y2
}
running = True

#run the doublependulum fucntion
start timer at millisec = 0
while running = true run following code every 10 milisec:
    if (millisec > time){
        running = False
    }
    doublependulum(start1, start2, milisec)

    #put the durations in the list
    if(x1 => 0 && prevx1 =< 0 || x1 =< 0 && prevx1 => 0){
        kick.append(millisec)
    }
    if(x2 => 0 && prevx2 =< 0 || x2 =< 0 && prevx2 => 0){
        snare.append(millisec)
    }
    if(a2 => 0 && preva2 =< 0 || a2 =< 0 && preva2 => 0){
        hihat.append(millisec)
    }
    # make an history for the pendulum
    prevx1 = x1
    prevx2 = x2
    preva2 = a2


actualKick = []
actualSnare = []
actualHihat = []

# finds the first hit to know where the sequence starts
firstHit = [kick(0), snare(0), hihat(0)]
firstHit.sort()

# removes the silent time before the sequence
for f in range kick:
    actualkick.append = kick(f) - firstHit(0)
for g in range snare:
    actualSnare.append = snare(g) - firstHit(0)
for h in range hihat:
    actualHihat.append = hihat(h) - firstHit(0)

# this forloop creates grids or timesignatures in the same timespan in miliseconds,
# it checks how much the kick deviates from these timesignatures and makes an
# array of the deviation per time signature
for i in range(3, 23, 2):

    # defines the duration of one beat on the grid
    totalOffSet = 0
    beat = (time - firstHit(0))/i
    grid = []

    # makes a grid in an array
    for j in range(0, i):
        grid.append(beat * j)

    # calculates how much the kick deviates from the grid to later choose the smallest offset
    for k in actualKick:
        #find the closest beat to the kick:
        closeBeat = "closest"(grid)
        offSet = math.fabs(closeBeat - k)
        totalOffSet = totalOffSet + offSet
    offSets.append(totalOffSet)

# chooses the time signature that has the smallest offset
smallest = min(offSets)
timeSig = offSets.index(smallest)*2+3
beatDur = time/timeSig

# makes the best fitting time signature
actualGrid = []
for l in range(0, timeSig):
    actualGrid.append(beatDur * l)

# function to quantize a list
def quantizeList(list, gridList, quantizedList)
for hit in list:
    # find the closest beat:
    quantizeBeat = "closest"(list)
    actualOffSet = quantizeBeat - hit
    quantizedList.append(hit + actualOffSet)
    return quantizedList

# using the function above to quantize the kick snare and hihat
quantizeList(actualKick, actualGrid, quantizedKick)
quantizeList(actualSnare, actualGrid, quantizedSnare)
quantizeList(actualHihat, actualGrid, quantizedHihat)

# make list of note durations:
def makeMidiArray(array, midiArray):
    for m in range(0, array):
        midiArray = ((quantizedKick[m + 1])-(quantizedKick[m]))/beatDur
        midiArray.append(midiArray)
        return midiArray

# make lists of the midi notes for each drum
makeMidiArray(quantizedKick, midiKick)
makeMidiArray(quantizedSnare, midiSnare)
makeMidiArray(quantizedHihat, midiHihat)
