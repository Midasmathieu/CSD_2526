
brightness = input("How bright do you want the kick to be 1 to 10?");
kickBrightness = validateUserInput(brightness);
peakFrequency = scale(kickBrightness, 300, 900);
envelope0.setPeak(peakFrequency);

boominess = input("How boomy do you want the kick to be 1 to 10?");
kickBoominess = validateUserInput(boominess);
releaseInSeconds = scale(kickBoominess, 1000, 5000);
releaseInSamples = releaseInSeconds * samplerate;
envelope1.setRelease(releaseInSamples);

glassiness = input("How glassy do you want the kick to be 1 to 10?")
kickGlassiness = validateUserInput(glassiness);
attackInMilliseconds = scale(kickGlassiness, 0, 10);
attackInSamples = attackInSeconds * samplerate * 0.001;
envelope0.setAttack(attackInSamples);


# code per sample
frequency = envelope0.getSample();
amplitude = envelope1.getSample();
sine.setFreq(frequency);
output = sine.getSample * amplitude;
