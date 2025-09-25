myList = [4, 1, 88, 44, 3]
for myNumber in range(0, 100, 5):
    iets = min(myList, key=lambda x:abs(x-myNumber))
    print(iets)
