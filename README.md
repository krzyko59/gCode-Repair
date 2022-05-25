# gCode Repair
**Program konsolowy pisany w języku C++ (visual studio) na platformę Windows**</br>
**Przekształcający kod maszynowy (GCODE), maszyny marki ECKERT, generowany przez program Lantek**</br></br>
Program ten: </br>
- udoskonala kod maszynowy o funkcje które nie są możliwe do wdrożenia bezpośrednio z programu do generowania GCODE</br>
- dostosowuje gotowe programy maszynowe do specyficznych sytuacji</br>
- wzbogaca gotowe programy maszynowe o funkcjonalności, których ponowne stworzenie jest czasochłonne</br>
- ułatwia prace operatora(operator nie musi manualnie regulować predkości)</br>
![screen 1](https://github.com/krzyko59/gCode-Repair/blob/main/screen_1.png?raw=true)</br>
![screen 2](https://github.com/krzyko59/gCode-Repair/blob/main/screen_4.png?raw=true)</br>
![screen 3](https://github.com/krzyko59/gCode-Repair/blob/main/screen_2.png?raw=true)</br>
![screen 4](https://github.com/krzyko59/gCode-Repair/blob/main/screen_3.png?raw=true)</br>
</br>Instrukcja:
- a) uruchomić program, przeciągnąć plik *.NCP do konsoli, wcisnąć enter.
- b) przeciągnąć plik *.NCP bezpośrednio na ikone programu gCode repair
- postępować zgodnie z komunikatami wyświetlanymi w konsoli.
</br>Wymagania:
- 
</br>Zasady działania programu:
- program wczytuje treść pliku *.NCP
- wycina numeracje N<numer lini>
- normalizuje zapisy (np.G01, g01, g1 na G1)
- [1] 
- - szuka obrysu zewnetrzego sita
- - zczytuje i oblicza wielkość, pozycje koła
- - generuje nowe koło uwzględniając korekcje braku kalibracji głowicy, dodając polecenia do ukosowania głowicy 3D
- [4]
- - podmienia lub dodaje parametr C na C180
- dodaje poniwnie numeracje N<numer lini>
- zapisuje plik do folderu z którego został wczytany o nazwie [nazwa pliku bazowego]_gCr.NCP
