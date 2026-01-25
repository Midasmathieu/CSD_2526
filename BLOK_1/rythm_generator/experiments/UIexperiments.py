

exampleQuestion = 'What drumkit do you want to select?'
exampleOptions = ['autechre kit', 'dark kit']

def retrieveUserOption(question, options):
    if(not str(question)):
        raise TypeError(
            'awkward error....'
        )

    else:
        selectedOption = 1
        correctInput = False

        while (not correctInput):
            print(question)
            for i, option in enumerate(options):
                print(i +1, ':', option)
            print('leave empty for option 1')
            userInput = input()

            if not userInput:
                correctInput = True

            else:
                try:
                    inputIndex = int(userInput)
                    if (inputIndex >= 1 and inputIndex <= len(options)):
                        selectedOption = inputIndex

                        correctInput = True

                    else:
                        raise TypeError(
                            'awkward... trow error....'
                        )
                except:
                    print('BUMMER! that no make the sense dud. \n' +
                        'try again dud...\n' + 'bummer mann-person.\n\n')
        selectedOption -= 1

    return selectedOption

drumIndex = retrieveUserOption(exampleQuestion, exampleOptions)
print( exampleOptions[drumIndex])
