stappenplan:

0.  Maak array kick, snare, hihat, quantizedKick, quantizedSnare, quantizedHihat
    midiKick, midiSnare en midiHihat aan.

1.  Maak een pendulum aan (pendulum1) en zorg via een functie dat pendulum1 kan bewegen,
    gebruik om het gedrag van een echte pendulum na te boodsen de lagrangian formule
    die voor de tijd in milliseconden de hoek van pendulum1 teruggeeft en de
    coordinaten van het einde van de pendulum uitrekend en teruggeeft.

2.  Schrijf in dezelfde functie een tweede pendulum (pendulum2) die aan pendulum1 hangt
    en ook beweegt door middel van de lagrangian formule. Laat deze ook de hoek, x
    en y coordinaten van het uiteinde teruggeven.

3.  Maak buiten deze functie een aantal if statements aan die hetvolgende checken:
      - Gaat het uiteinde van pendulum1 door de Y-as?
      - Gaat het uiteinde van pendulum2 door de Y-as?
      - Staat pendulum2 recht naar beneden?

4.  Laat de gebruiker kiezen waar de dubbele pendulum start door de hoeken van de
    pendulums in graden te geven en hoelang die zwaait (in miliseconden).

4.  Laat de dubbele pendulum zwaaien en start een timer, en laat de voorgenoemde if statements het volgende doen:
      - pendulum1 door Y-as --> voeg de waarde van de timer op dat moment toe aan de kick array.
      - pendulum2 door Y-as --> voeg de waarde van de timer op dat moment toe aan de snare array.
      - pendulum2 recht naar beneden --> voeg de waarde van de timer op dat moment toe aan de hihat array
    Nu hebben we 3 arrays met timestamps wanneer de kick, snare en hihat moeten beginnen.

5.  Omdat we willen dat de eerste drum hit ook op de eerste tel komt trekken we bij elke
    interger in de array het eerste interger (index = 0) van de array af.
    Dus een array [3, 7, 8] wordt [0, 4, 5].

6.  De dubbele pendulum is een chaotisch systeem dat niet aan een maatsoort is gebonden.
    Om te zorgen dat er toch een maatsoort wordt gekozen nemen we aan dat de tijd waarin de pendulum
    zwaait, een maat is. We gaan in een forloop onderzoeken welke maatsoort het beste past bij het ritme.

7.  Maak in een forloop verschillende grids aan en vergelijk ze met de kick array timestamps, kijk per
    timestamp wat het (absolute) verschil is met de dichtbij zijnde tel in het grid.

8.  Tel per maatsoort al die (absolute) verschillen bij elkaar op en check welke het kleinste verschil
    heeft van het grid. (door alle opgetelde verschillen in een array te zetten en de kleinste eruit te pikken)

9.  Quantize het kick patroon naar de best passende maatsoort door de (niet absolute) verschillen
    van elke drum hit met de dichtstbij zijnde tel bij de drumhit op te tellen en stop het in de quantized arrays

10. Vul in een forloop de midi arrays door de volgende drumhit - de huidige drumhit te
    doen en dat te delen door de duratie van een beat. Nu heb je een array met midi waardes van elke drumhit.
