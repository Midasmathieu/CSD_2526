correctInput = False

a1 = 90

while (not correctInput):
    userA1 = input("Where do you want pendulum 1 to start in degrees? (leave empty for 90 degrees)")

    if not userA1:
        correctInput = True
    else:
        try:
            a1 = float(userA1)
            if a1 > 0 and a1 < 360:
                correctInput = True
            else:
                a1 = 90
                print("a circle has a minimum of 0 and a maximum of 360 degrees")

        except:
            print("nah dawg try again")

print("hell ye angle is: ", a1)
