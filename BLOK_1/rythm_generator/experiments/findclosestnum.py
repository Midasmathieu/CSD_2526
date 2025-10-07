import math

#TODO: check if totalOffSets works proporly

kickSnare = [1, 4, 5, 7]
grid = [0, 2, 4, 8]

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
    print("beat: ", closestbeat)
    print("offset: ", relativeOffSet)
