import pygame
import time as t
pygame.init()
kick = pygame.mixer.Sound('kick.mp3')
snare = pygame.mixer.Sound('snare.mp3')
hihat = pygame.mixer.Sound('hihat.mp3')

list = [{'sound': kick, 'duration': 0.44999999999999996, 'velocity': 113.59703769908165},
        {'sound': hihat, 'duration': 0.5333333333333333, 'velocity': 73.694099980866},
        {'sound': snare, 'duration': 0.733333333333334, 'velocity': 49.334247720638515},
        {'sound': kick, 'duration': 1.0833333333333344, 'velocity': 41.07081163676675},
        {'sound': snare, 'duration': 1.4166666666666665, 'velocity': 101.85915372763263},
        {'sound': hihat, 'duration': 1.4166666666666665, 'velocity': 82.23797155202655},
        {'sound': kick, 'duration': 1.4333333333333331, 'velocity': 84.18127581461412},
        {'sound': kick, 'duration': 1.866666666666665, 'velocity': 42.28601023884681},
        {'sound': snare, 'duration': 2.0999999999999974, 'velocity': 65.9859704470356},
        {'sound': hihat, 'duration': 2.33333333333333, 'velocity': 67.81360121147696},
        {'sound': kick, 'duration': 2.466666666666663, 'velocity': 97.09176177848025},
        {'sound': snare, 'duration': 2.666666666666662, 'velocity': 39.03280785915448},
        {'sound': hihat, 'duration': 3.2833333333333266, 'velocity': 94.26322253930316},
        {'sound': kick, 'duration': 3.349999999999993, 'velocity': 127},
        {'sound': snare, 'duration': 3.3666666666666596, 'velocity': 106.15920157711274}]

# def create_dictionary(first, second, third):
#     return {
#         "first": first,
#         "second": second,
#         "third": third
#     }


def handle_note_event(sample, velocity):
    # sample.set_volume(velocity / 127.0)
    sample.play()


# for i in range(0, 5):
#     dictionary1 = create_dictionary("kick", i*2, i*3)
#     list.append(dictionary1)
for i in range(0, len(list)):
    print(list[i].get('sound'))



onemoretime = input("hey booosss do you want to hear that #onemoretime??... yes or no boosssss...")
if onemoretime == "yes":
    running = True
    sampleSound = list[0].get('sound')
    sampleVelocity = list[0].get('velocity')
    ts = list.pop(0).get('duration')
else:
    running = False

time_zero = t.time()

while running == True:
    currentTime = t.time() - time_zero
    if (currentTime > ts):
        handle_note_event(sampleSound, sampleVelocity)
        if list:
            # ts = list[0].get('duration')
            sampleSound = list[0].get('sound')
            sampleVelocity = list[0].get('velocity')
            ts = list.pop(0).get('duration')
            # print(list[0].get('duration'))
        else:
            print(list)
            break


t.sleep(0.001)
