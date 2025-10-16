import UI_functions
pendulumQuestion1 = 'How many degrees do you want to set pendulum 1? \n 0 to 360 degrees. (default = 90 degrees) \n'
pendulumQuestion2 = 'How many degrees do you want to set pendulum 2? \n 0 to 360 degrees. (default = 90 degrees)\n'
generalError = 'oh oh error, try again...'
kitQuestion = 'what sample pack do you want to select?'
kitOptions = ['de ãtechre', 'dark vibes dud\n']

anglePendulum1 = UI_functions.retrieveUserInput(0, 360, 90, pendulumQuestion1, generalError, ' degrees it is!\n')
anglePendulum2 = UI_functions.retrieveUserInput(0, 360, 90, pendulumQuestion2, generalError, ' degrees it is!\n')

timeQuestion = 'How long do you want the pendulum to swing in seconds?\n 2 to 7 degrees. (default = 4 seconds)\n'
secondsRunning = UI_functions.retrieveUserInput(2, 7, 4, timeQuestion, generalError, ' seconds it is!\n')

selectedKit = UI_functions.retrieveUserOption(kitQuestion, kitOptions)

signatureQuestion = "what time signature do you want to quantize that to?"
signatureOptions = ['5/4', '7/4', '9/4', '11/4', '13/4 because you are a little pretentious fucking guy...\n']

selectedSignature = UI_functions.retrieveUserOption(signatureQuestion, signatureOptions)


BPMQuestion = 'How fast do you want to play it back? Enter BPM... (default = 120)\n'
selectedBPM = UI_functions.retrieveUserInput(60, 220, 120, BPMQuestion, generalError, 'Beats per minute it is!\n')

# correctInput2 = False
# while (not correctInput2):
#     givenUserInput2 = function.retrieveUserFloat("howmany degrees do you want the pendulum2 to be?\n")
#     validUserInput2, correctInput2 = function.checkUserFloat(givenUserInput2, 0, 360, 90, generalError, correctInput2)
# print("Succeeded, angle is: ", validUserInput2)
