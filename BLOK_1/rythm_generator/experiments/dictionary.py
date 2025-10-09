import pygame
import time as t
pygame.init()
kick = pygame.mixer.Sound('kick.mp3')
snare = pygame.mixer.Sound('snare.mp3')
hihat = pygame.mixer.Sound('hihat.mp3')

def get_currentFrameTime(drums):
    return drums["currentFrameTime"]

drums = [{'sound': kick, 'currentFrameTime': 0.44999999999999996, 'velocity': 113.59703769908165},
        {'sound': hihat, 'currentFrameTime': 0.5333333333333333, 'velocity': 73.694099980866},
        {'sound': snare, 'currentFrameTime': 0.733333333333334, 'velocity': 49.334247720638515},
        {'sound': kick, 'currentFrameTime': 1.0833333333333344, 'velocity': 41.07081163676675},
        {'sound': snare, 'currentFrameTime': 1.4166666666666665, 'velocity': 101.85915372763263},
        {'sound': hihat, 'currentFrameTime': 1.4166666666666665, 'velocity': 82.23797155202655},
        {'sound': kick, 'currentFrameTime': 1.4333333333333331, 'velocity': 84.18127581461412},
        {'sound': kick, 'currentFrameTime': 1.866666666666665, 'velocity': 42.28601023884681},
        {'sound': snare, 'currentFrameTime': 2.666666666666662, 'velocity': 39.03280785915448},
        {'sound': snare, 'currentFrameTime': 2.0999999999999974, 'velocity': 65.9859704470356},
        {'sound': hihat, 'currentFrameTime': 2.33333333333333, 'velocity': 67.81360121147696},
        {'sound': kick, 'currentFrameTime': 2.466666666666663, 'velocity': 97.09176177848025},
        {'sound': hihat, 'currentFrameTime': 3.2833333333333266, 'velocity': 94.26322253930316},
        {'sound': kick, 'currentFrameTime': 3.349999999999993, 'velocity': 127},
        {'sound': snare, 'currentFrameTime': 3.3666666666666596, 'velocity': 106.15920157711274}]

print("--- drums List ---")
for drum in drums:
    print(drum)
drums.sort(key=get_currentFrameTime)
print("--- drums List sorted by currentFrameTime ---")
for drum in drums:
    print(drum)

def handle_note_event(sample, velocity):
    # sample.set_volume(velocity / 127.0)
    sample.play()

for i in range(0, len(drums)):
    print(drums[i].get('sound'))


onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
if onemoretime == "yes":
    running = True
    sampleSound = drums[0].get('sound')
    sampleVelocity = drums[0].get('velocity')
    ts = drums.pop(0).get('currentFrameTime')
else:
    running = False

time_zero = t.time()

while running == True:
    currentTime = t.time() - time_zero
    if (currentTime > ts):
        handle_note_event(sampleSound, sampleVelocity)
        if drums:
            # ts = drums[0].get('currentFrameTime')
            sampleSound = drums[0].get('sound')
            sampleVelocity = drums[0].get('velocity')
            ts = drums.pop(0).get('currentFrameTime')
            # print(drums[0].get('currentFrameTime'))
        else:
            print(drums)
            break


t.sleep(0.001)
