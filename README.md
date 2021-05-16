# Torquemeter PRO
## Inleiding

Onze koppelmeter is van het type ‘Prony Brake’. Hierbij klemmen we een arm met gekende lengte rond een as zodat de draaibeweging wordt overgebracht op deze arm. Vervolgens meten we op het einde van de arm de kracht die wordt uitgeoefend als gevolg van de draaibeweging.

Omdat de lengte van de arm gekend is kunnen we erg gemakkelijk het koppel bepalen via de volgende formule:

$\tau=L\cdot F$

Deze arm wordt op zijn plaats geklemd door twee bouten die langs weerszijden van de as bevestigd worden. Om de as te beschermen hebben we een bronzen lager tussen de klem en de as. Tijdens het draaien zal deze eerder verslijten dan de klem en de hoofdas. Deze is daarom ook makkelijk vervangbaar.

## Onderdelen

### De load cell

Een load cell bestaat uit een folie met elektrische geleiders. Door vervorming wijzigt de weerstand van deze geleiders. Dit zorgt voor een signaal dat evenredig is aan de kracht die erop wordt uitgeoefend.

Voor onze opstelling gebruikten we een TAL220B 5kg load cell. Deze load cell heeft een spanning nodig van 3V-10V en heeft een meetbereik van 5kg. Deze load cell heeft 4 draden (rood, groen, zwart en wit).  Excitation spanning bepaalt het bereik waarin het uitgangssignaal zit.

### De load cell amplifier

Een load cell amplifier versterkt het signaal van de load cell. Dit is nodig omdat de load cell een zwak signaal geeft (dit komt omdat er anders plastische vervorming zal treden in de load cell).

We gebruiken de hx711 load cell amplifier. Je verbindt de draden van de load cell met de overeenkomstige kleur van de amplifier.

### De lichtsluis

We hebben de RE08A lichtsluis gebruikt. Deze lichtsluis heeft een voedingsspanning nodig 4,5V-5,5V. Met de lichtsluis meten we het aantal keren dat een tand van de schijf er doorheen gaat. Hieruit leiden we het aantal toeren per minuut af die de roterende as van de testbank maakt. Voor deze RPM-sensor hebben we zowel een houder als een schijf ge-3D-print.

## Gebruik

1. Zorg dat de arm en load cell geen contact maken
2. Controleer dat op het LCD-scherm het volgende zichtbaar is (Indien niet: zie “Het op- en afstellen van het project” deel: “**Arduino, LCD & Software”)**
3. Start de meting door de RC-wagen te versnellen.
4. Lees de meetgegevens af op het scherm of op de computer
5. Om het vermogen en de paardenkracht af te lezen: Druk op de zwarte knop onder het LCD-scherm.
