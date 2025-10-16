# def retrieveUserFloat(question):
#     userInput = input(question)
#     return(userInput)


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

def retrieveUserInput(minInput, maxInput, defaultInput, question, errorMessage, message):
    correctInput = False
    while (not correctInput):
        validUserInput, correctInput = checkUserFloat(minInput, maxInput, defaultInput, errorMessage, correctInput, question)
        if correctInput == True:
            print(validUserInput, message)
            return correctInput

def retrieveUserChoice(question, options):
    if(not str(question)):
        raise TypeError(
            'question needs to be a string')

    print(question)
    for i, option in enumerate(options):
        print(i + 1, ':', option)

    # print('left empty for default option 1 dude')
    return input()

def validateIntRange(value, rangeLow, rangeHigh):
    try:
        intValue = int(value)
        if (intValue >= rangeLow and intValue <= rangeHigh):
            return True
    except:
        return False

    return False

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
