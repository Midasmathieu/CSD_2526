import math

kick = [0, 12, 20, 47, 55, 73, 90]
snare = [0, 18, 34, 50, 58, 66, 74, 82]
tijd = 100
offSets = []

for i in range(3, 23, 2):
    totalOffSet = 0
    beat = tijd/i
    grid = []
# defines the duration of one beat on the grid
    for j in range(0, i):
        grid.append(beat * j)
# makes a grid
    for k in kick:
        closeBeat = min(grid, key=lambda x:abs(x-k))
# credit: kennytm on stack overflow
        offSet = math.fabs(closeBeat - k)
        totalOffSet = totalOffSet + offSet
# calculates how mutch the kick deviates from the grid
    offSets.append(totalOffSet)
print(offSets)
