samplerate = 44100

brightness = input("How bright do you want the kick to be 1 to 10?");
kickBrightness = validateUserInput(brightness);
peakFrequency = scale(kickBrightness, 300, 900);
pitchEnvelope.setPeak(peakFrequency);

boominess = input("How boomy do you want the kick to be 1 to 10?");
kickBoominess = validateUserInput(boominess);
releaseInSeconds = scale(kickBoominess, 1000, 5000);
releaseInSamples = releaseInSeconds * samplerate;
ampEnvelope.setRelease(releaseInSamples);

glassiness = input("How glassy do you want the kick to be 1 to 10?")
kickGlassiness = validateUserInput(glassiness);
attackInMilliseconds = scale(kickGlassiness, 0, 10);
attackInSamples = attackInMilliseconds * samplerate * 0.001;
pitchEnvelope.setAttack(attackInSamples);

class Synth() {
    void amplify(signal, numberToAmplificationWith);
    # void sum(signalsToSum);
    void startEnvelope(noteOn);
    void stopEnvelope(noteOff);
    void mtof(midi);
};

class KickSynth() {
    void pitchEnvelope.setDecay(0.3);
    void pitchEnvelope.setInitial(10000);
    void pitchEnvelope.setSustain(0.0);
    void pitchEnvelope.setRelease(0);
    void ampEnvelope.setPeak(1);
}

class Sine() {
    void setFreq();
    void calculatePhase(freq, 44100);
    float frequency;
    float phase;
    function calculateSample(phase);
};

list melody = [60, 64, 67, 70];


# sine.getsample rekend zogenaamd live een sine uit als je de frequentie erin zet

# code per sample
Synth.mtof(melody[current note]);

if (prevNote ≠ currentNote) {
    pitchEnvelope.stopEnvelope(noteOff);
    pitchEnvelope.startEnvelope(noteOn);
    ampEnvelope.stopEnvelope(noteOff);
    ampEnvelope.startEnvelope(noteOn);
}

frequency = pitchEnvelope.getSample();
amplitude = ampEnvelope.getSample();

sine.setFreq(frequency);
sample = sine.calculateSample();
output = Synth.amplify(samlpe, amplitude);

#AND THEN TO JUCE!!!!!!!!! AND BEYOND!!!!!!!!!
