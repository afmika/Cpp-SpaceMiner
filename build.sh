# On defini les includes non propre au projet pour eviter les erreurs de compilation
g++ -Wall -g -I include -I "./include" -c classes/*.cpp
g++ -Wall -g -I include -I "./include" -c *.cpp

# On definie le resultat du build + les fichiers obj a lier + les librairies dans dans /lib
g++ -L "./lib" -o "./bin/afspace-miner" *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# Lance l'application
./bin/afspace-miner