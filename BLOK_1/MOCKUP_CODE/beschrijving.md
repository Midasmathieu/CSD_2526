ritme generatie strategie:

Mijn idee om een ritme te genereren is om een kick, snare en hihat te
laten triggerendoor de posities van de uiteindes van de dubbele pendulum.

zowel een voordeel als een nadeel is dat de dubbele pendulum vrij chaotisch is,
er kunnen dus veel ritmes mee worden gegenereerd, maar het is niet zeker of
die ook goed klinken. De quantize strategie neigt ook per definitie naar
preciezere maatsoorten (liever 23/16 dan 3/4). Deze "design flaws" maken dat
de software goed moet worden afgesteld om het te laten doen wat ik wil.

Een andere design flaw is dat de pendulum aan het begin vaak niet heel
chaotisch beweegt, het zou dus kunnen zijn dat de variatie enkel aan het einde
hoorbaar wordt. Ook zit er tijd tussen het loslaten van de pendulum en het
triggeren van de eerste drumhit. Wat dingen die wederom maken dat het een te
goed gefinetuned systeem moet zijn.

Het pendulum gedrag wordt door middel van de lagrangian formule gesimuleert.
Dat is een lange complexe formule die veel inputs nodig heeft om te werken.
Ook is het een formule waar sinusen en cosinussen in voor komen. Dat betekent
dat de math library van python essentieel is.

De strategie heeft baad bij een visualizer, mijn plan is om de pendulum met behulp
van pygame te animeren. Dat betekend dus wel dat de code live rund en dus niet
direct gequantized kan worden gegenereerd (omdat anders de animatie ook
wordt gequantized).

Een voordeel van deze strategie is dat binnen bepaalde start waardes de
dubbele pendulum niet chaotisch beweegt (maar loopt).
In de niet chaotische gebieden is dus herhaling en ritme, dit kan ik binnen
mijn software gebruiken maar vereist wel eerst verder onderzoek.
