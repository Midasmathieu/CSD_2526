# checks if an input is an float and in range
def checkUserFloat(minInput, maxInput, defaultInput, errorMessage, correctInput, question):
    correctInput = correctInput
    userInput = input(question)
    if not userInput:
        # empty string --> use default
        userFloat = defaultInput
        print('left empty for default:')
        correctInput = True
    else:
        try:
            userFloat = float(userInput)
            if userFloat >= minInput and userFloat <= maxInput:
                correctInput = True
            else:
                print(errorMessage)

        except:
            print(errorMessage)
            return defaultInput, correctInput

    return userFloat, correctInput

# gets userFloat and returns it or returns default input
def retrieveUserInput(minInput, maxInput, defaultInput, question, errorMessage, message):
    correctInput = False
    while (not correctInput):
        validUserInput, correctInput = checkUserFloat(minInput, maxInput, defaultInput, errorMessage, correctInput, question)
        if correctInput == True:
            print(validUserInput, message)
            return validUserInput

# gets the choice from user
def retrieveUserChoice(question, options):
    if(not str(question)):
        raise TypeError(
            'question needs to be a string')

    print(question)
    for i, option in enumerate(options):
        print(i + 1, ':', option)

    return input()

# check if userinput is an interger and in range
def validateIntRange(value, rangeLow, rangeHigh):
    try:
        intValue = int(value)
        if (intValue >= rangeLow and intValue <= rangeHigh):
            return True
    except:
        return False

    return False

# gets user input and selects option
def retrieveUserOption(question, options):
    selectedOption = 1
    correctInput = False
    while(not correctInput):
        userInput = retrieveUserChoice(question, options)
        if(validateIntRange(userInput, 1, len(options))):
            selectedOption = int(userInput)
            correctInput = True

        elif(not userInput):
            correctInput = True
            print('left empty for option 1:')
        else:
            print('incorrect input, try again of fuck off dud.\n\n')

    selectedOption -= 1
    print('you ave chosen.... ', options[selectedOption], '\n')
    return options[selectedOption]
