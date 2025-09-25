kick = []
snare = []
hihat = []

function setup() {
    degrees1 = float(input("where do you want pendulum1 to start in degrees?: "))
    start1 = degrees1 * math.pi / 180 / math.pi
    degrees2 = float(input("where do you want pendulum2 to start in degrees?: "))
    start2 = degrees1 * math.pi / 180 / math.pi
    time = input("how long do you want the double pendulum to run?")

 for (i = 0; i < time; i++)
    Lagrangian formula pendulum1;
    Langangian formula pendulum2;
    if (pendulum1 x = 0){   #dit zou je ook kunnen schrijven als match case, misschien handiger dan lange if elif lijsten -> https://www.geeksforgeeks.org/python/python-match-case-statement/
        kick.append(i);
    }
    if (pendulum2 x = 0){
        snare.append(i);
    }
    if (pendulum2 π = 0){   #voor mij is het soortvan logischer om gewoon met graden te rekenen ipn pi, maar misschien snap ik rekenen met pi gewoon nog niet zo goed haha.
        hihat.append(i);    #maar je zou hier bijvoorbeeld if (degr_pendulum2 == 0){do stuff}, hiermee bedoel ik met degr gewoon degree of 'graden'
    }
}

for i in range(3, 23, 2):   #
    totalOffSet = 0
    beat = time/i           #waarschijnlijk time in seconden? delen door de forloop nr
    grid = []
# defines the duration of one beat on the grid
    for j in range(0, i):
        grid.append(beat * j)
# makes a grid
    for k in kick:
        closeBeat = min(grid)
        offSet = math.fabs(closeBeat - k) #abs is also in python
        totalOffSet = totalOffSet + offSet
# calculates how mutch the kick deviates from the grid to later choose the smallest offset
    offSets.append(totalOffSet)

smallest = min(offSets)
timeSig = offSets.index(smallest)*2+3
beatDur = time/timeSig
actualGrid = []
quantizedKick = []

for l in range(0, timeSig):
    actualGrid.append(beatDur * l)
for m in kick:
    quantizeBeat = min(actualGrid)
    actualOffSet = quantizeBeat - m
    quantizedKick.append(m + actualOffSet)

#–
#make list of note durations:
midiArray = []
for m in range(0, kick):
    midiArray = ((kick[m + 1])-(kick[m]))/beatDur
    midiArray.append(midiArray)
