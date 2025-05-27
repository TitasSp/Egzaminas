
# Egzaminas

C++ programa skirta tekstinių failų analizei. Ji atlieka šiuos veiksmus:

- Skaičiuoja žodžių pasikartojimą
- Nustato pasikartojančius žodžius ir jų eilučių numerius
- Išskiria ir išsaugo visus URL adresus
- Išveda rezultatus į atskirus failus

## Diegimas

1. **Klonuokite repozitoriją:**

```bash
git clone https://github.com/TitasSp/Egzaminas.git
cd Egzaminas
```

2. **Kompiliuokite programą:**

Naudodami `g++`:

```bash
g++ -std=c++17 -o main main.cpp
```

Arba naudokite kitą C++ kompiliatorių su C++17 ar naujesne versija.
## Arba

```Naudojant CMake
mkdir build
cd build
cmake ..
cmake --build .
```
## Naudojimas

1. **Paruoškite įvesties failą:**

Sukurkite `input.txt` failą tame pačiame kataloge. Šiame faile turi būti tekstas, kurį norite analizuoti.

2. **Paleiskite programą:**

```bash
.\main.exe
```

3. **Rezultatai:**

Programa sugeneruos tris išvesties failus:

- `output.txt`: Pasikartojantys žodžiai ir jų dažnis
- `cross_reference.txt`: Eilučių numeriai, kur pasikartoja žodžiai
- `urls.txt`: Rasti unikalūs URL adresai

## Failų struktūra

```
.
├── input.txt                # Įvesties tekstinis failas
├── main.cpp                 # C++ programos kodas
├── output.txt               # Pasikartojančių žodžių išvestis
├── cross_reference.txt      # Žodžių pasikartojimo eilutėse išvestis
├── urls.txt                 # Išskirti URL adresai
```


