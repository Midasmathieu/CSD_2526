
#
kick = []
snare = []
hihat = []
quantizedKick = []
quantizedSnare = []
quantizedHihat = []

    degrees1 = float(input("where do you want pendulum1 to start in degrees?: "))
    start1 = degrees1 * math.pi / 180 / math.pi
    degrees2 = float(input("where do you want pendulum2 to start in degrees?: "))
    start2 = degrees1 * math.pi / 180 / math.pi
    time = input("how long do you want the double pendulum to run in miliseconds?")

function doublependulum(a1, a2){
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
    a1_v = a1_v + a1_a * delta_time * 0.1
    a1 = a1 + a1_v
    a2_v = a2_v + a2_a * delta_time * 0.1
    a2 = a2 + a2_v
    return a1, a2
    #calculate the xy positions and return them
    x1 = r1 * math.sin(a1)
    y1 = r1 * math.cos(a1)
    x2 = x1 + r2 * math.sin(a2)
    y2 = y1 + r2 * math.cos(a2)
    return x1, y1, x2, y2
}


start timer at millisec = 0
if(milisec < time){
    doublependulum(start1, start2)
}
else {
    stop timer
}
if(x1 => 0 && prevx1 =< 0 || x1 =< 0 && prevx1 => 0){
    kick.append(millisec)
}
if(x2 => 0 && prevx2 =< 0 || x2 =< 0 && prevx2 => 0){
    snare.append(millisec)
}
if(a2 => 0 && preva2 =< 0 || a2 =< 0 && preva2 => 0){
    hihat.append(millisec)
}

prevx1 = x1
prevx2 = x2
preva2 = a2
