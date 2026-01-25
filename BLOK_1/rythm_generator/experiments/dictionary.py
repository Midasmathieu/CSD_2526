import pygame
import time as t
pygame.init()
kick = pygame.mixer.Sound('kick.mp3')
snare = pygame.mixer.Sound('snare.mp3')
hihat = pygame.mixer.Sound('hihat.mp3')

def get_currentFrameTime(drums):
    return drums["currentFrameTime"]

velocityList = [113.59703769908165, 73.694099980866, 49.334247720638515, 41.07081163676675, 101.85915372763263, 82.23797155202655, 84.18127581461412, 42.28601023884681, 65.9859704470356, 67.81360121147696, 97.09176177848025, 39.03280785915448, 94.26322253930316, 127, 106.15920157711274, 113.59703769908165, 73.694099980866, 49.334247720638515, 41.07081163676675]
quantizedKick = [0.2631578947368421, 1.0526315789473684, 1.5789473684210527, 2.1052631578947367, 2.894736842105263, 3.6842105263157894, 4.2105263157894735]
quantizedSnare = [0.0, 1.0526315789473684, 1.8421052631578947, 2.894736842105263, 3.9473684210526314]
quantizedHihat = [0.0, 0.5263157894736842, 1.0526315789473684, 1.3157894736842104, 2.1052631578947367, 2.894736842105263, 3.6842105263157894]

drums = []
# drums = [{'sound': kick, 'currentFrameTime': 0.44999999999999996, 'velocity': 113.59703769908165},
#         {'sound': hihat, 'currentFrameTime': 0.5333333333333333, 'velocity': 73.694099980866},
#         {'sound': snare, 'currentFrameTime': 0.733333333333334, 'velocity': 49.334247720638515},
#         {'sound': kick, 'currentFrameTime': 1.0833333333333344, 'velocity': 41.07081163676675},
#         {'sound': snare, 'currentFrameTime': 1.4166666666666665, 'velocity': 101.85915372763263},
#         {'sound': hihat, 'currentFrameTime': 1.4166666666666665, 'velocity': 82.23797155202655},
#         {'sound': kick, 'currentFrameTime': 1.4333333333333331, 'velocity': 84.18127581461412},
#         {'sound': kick, 'currentFrameTime': 1.866666666666665, 'velocity': 42.28601023884681},
#         {'sound': snare, 'currentFrameTime': 2.666666666666662, 'velocity': 39.03280785915448},
#         {'sound': snare, 'currentFrameTime': 2.0999999999999974, 'velocity': 65.9859704470356},
#         {'sound': hihat, 'currentFrameTime': 2.33333333333333, 'velocity': 67.81360121147696},
#         {'sound': kick, 'currentFrameTime': 2.466666666666663, 'velocity': 97.09176177848025},
#         {'sound': hihat, 'currentFrameTime': 3.2833333333333266, 'velocity': 94.26322253930316},
#         {'sound': kick, 'currentFrameTime': 3.349999999999993, 'velocity': 127},
#         {'sound': snare, 'currentFrameTime': 3.3666666666666596, 'velocity': 106.15920157711274}]


def lists_to_dictionary_list(list, sampleName):
    for number in list:
        drums.append({
            'sound': sampleName,
            'currentFrameTime': number
    })


lists_to_dictionary_list(quantizedKick, kick)
lists_to_dictionary_list(quantizedSnare, snare)
lists_to_dictionary_list(quantizedHihat, hihat)



print("--- drums List ---")
for drum in drums:
    print(drum)

drums.sort(key=get_currentFrameTime)

print("--- drums List sorted by currentFrameTime ---")
for drum in drums:
    print(drum)

for drum in drums:
    # print(drum)
    drum['velocity'] = velocityList[drums.index(drum)]

print("--- drums List sorted by currentFrameTime ---")
for drum in drums:
    print(drum)

def handle_note_event(sample, velocity):
    sample.set_volume(velocity / 127.0)
    sample.play()

# for i in range(0, len(drums)):
#     print(drums[i].get('sound'))


onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
if onemoretime == "yes":
    running = True
    sampleSound = drums[0].get('sound')
    sampleVelocity = drums[0].get('velocity')
    ts = drums.pop(0).get('currentFrameTime')
    handle_note_event(sampleSound, sampleVelocity)
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
