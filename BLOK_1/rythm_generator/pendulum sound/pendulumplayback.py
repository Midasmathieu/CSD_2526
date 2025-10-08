import pygame
import time as t
pygame.init()
kicksound = pygame.mixer.Sound('kick.mp3')
quantizedKick = [0.2631578947368421, 1.0526315789473684, 1.5789473684210527, 2.1052631578947367, 2.894736842105263, 3.6842105263157894, 4.2105263157894735]

onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
if onemoretime == "yes":
    running = True
    ts = quantizedKick.pop(0)
else:
    running = False

time_zero = t.time()

while running == True:
    currentTime = t.time() - time_zero
    if (currentTime > ts):
        kicksound.play()
        if quantizedKick:
            ts = quantizedKick.pop(0)

        else:
            break
