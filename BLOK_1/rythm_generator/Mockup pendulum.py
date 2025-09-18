kick = []
snare = []
hihat = []

function setup() {
 start1 = float(input("where do you want pendulum1 to start? (0 to 2π")) #graden van de hoek invullen is misschien logischer voor de gebruiker
 start2 = float(input("where do you want pendulum2 to start? (0 to 2π"))
 time = input("how long do you want the double pendulum to run?") #wat vul je in? hoeveelheid seconden, hoeveel bars enn is er een time signiture?

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
        offSet = math.fabs(closeBeat - k)
        totalOffSet = totalOffSet + offSet
# calculates how mutch the kick deviates from the grid
    offSets.append(totalOffSet)

#
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
