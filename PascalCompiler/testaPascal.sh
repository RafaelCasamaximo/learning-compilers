make
make clean

mkdir ./SaidaPascalSamples1
mkdir ./SaidaPascalSamples2

./pascal < ./PascalSamples1/tc01.pas > ./SaidaPascalSamples1/saida_01.txt
./pascal < ./PascalSamples1/tc02.pas > ./SaidaPascalSamples1/saida_02.txt
./pascal < ./PascalSamples1/tc03.pas > ./SaidaPascalSamples1/saida_03.txt
./pascal < ./PascalSamples1/tc04.pas > ./SaidaPascalSamples1/saida_04.txt
./pascal < ./PascalSamples1/tc05.pas > ./SaidaPascalSamples1/saida_05.txt
./pascal < ./PascalSamples2/tc01.pas > ./SaidaPascalSamples2/saida_01.txt
./pascal < ./PascalSamples2/tc02.pas > ./SaidaPascalSamples2/saida_02.txt
./pascal < ./PascalSamples2/tc03.pas > ./SaidaPascalSamples2/saida_03.txt
./pascal < ./PascalSamples2/tc04.pas > ./SaidaPascalSamples2/saida_04.txt
./pascal < ./PascalSamples2/tc05.pas > ./SaidaPascalSamples2/saida_05.txt
./pascal < ./PascalSamples2/tc06.pas > ./SaidaPascalSamples2/saida_06.txt
./pascal < ./PascalSamples2/tc07.pas > ./SaidaPascalSamples2/saida_07.txt
./pascal < ./PascalSamples2/tc08.pas > ./SaidaPascalSamples2/saida_08.txt
./pascal < ./PascalSamples2/tc09.pas > ./SaidaPascalSamples2/saida_09.txt
./pascal < ./PascalSamples2/tc10.pas > ./SaidaPascalSamples2/saida_10.txt

clear

diff ./SaidaPascalSamples1/saida_01.txt ./PascalSamples1/saida_01.txt
diff ./SaidaPascalSamples1/saida_02.txt ./PascalSamples1/saida_02.txt
diff ./SaidaPascalSamples1/saida_03.txt ./PascalSamples1/saida_03.txt
diff ./SaidaPascalSamples1/saida_04.txt ./PascalSamples1/saida_04.txt
diff ./SaidaPascalSamples1/saida_05.txt ./PascalSamples1/saida_05.txt
diff ./SaidaPascalSamples2/saida_01.txt ./PascalSamples2/saida_01.txt
diff ./SaidaPascalSamples2/saida_02.txt ./PascalSamples2/saida_02.txt
diff ./SaidaPascalSamples2/saida_03.txt ./PascalSamples2/saida_03.txt
diff ./SaidaPascalSamples2/saida_04.txt ./PascalSamples2/saida_04.txt
diff ./SaidaPascalSamples2/saida_05.txt ./PascalSamples2/saida_05.txt
diff ./SaidaPascalSamples2/saida_06.txt ./PascalSamples2/saida_06.txt
diff ./SaidaPascalSamples2/saida_07.txt ./PascalSamples2/saida_07.txt
diff ./SaidaPascalSamples2/saida_08.txt ./PascalSamples2/saida_08.txt
diff ./SaidaPascalSamples2/saida_09.txt ./PascalSamples2/saida_09.txt