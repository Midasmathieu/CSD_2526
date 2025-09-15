kick = []
snare = []
hihat = []

function setup() {
 start1 = float(input("where do you want pendulum1 to start? (0 to 2π"))
 start2 = float(input("where do you want pendulum2 to start? (0 to 2π"))
 time = input("how long do you want the double pendulum to run?")

 for (i = 0; i < time; i++)
    Lagrangian formula pendulum1;
    Langangian formula pendulum2;
    if (pendulum1 x = 0){
        kick.append(i);
    }
    if (pendulum2 x = 0){
        snare.append(i);
    }
    if (pendulum2 π = 0){
        hihat.append(i);
    }
}

for i in range(3, 23, 2):
    totalOffSet = 0
    beat = time/i
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

smallest = min(offSets)
offSets.index(smallest)

function loop() {
}
