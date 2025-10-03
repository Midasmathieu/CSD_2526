import pygame
import time
durations = [0.33, 0.33, 0.66]

# init  mixer module
pygame.init()
sample = pygame.mixer.Sound("BRONX KCK (13).WAV")
playing = 0
# load and play the sample
for i in durations:
    sample.play()
    time.sleep(i)
else:
    print("finished?")

# wait till sound is done playing before exiting
