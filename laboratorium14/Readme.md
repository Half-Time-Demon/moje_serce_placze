# Laboratorium 14 **Algorytmy kompresji danych**  (2023-06-13)

- W tym katalogu utworzyć katalog - `NazwiskoImie`
- Wypełnia zadania:
    - [Transformacja Burrowsa-Wheelera](#BWT) programu [BWT.c](./BWT.c) Zamienic funkcje. Dopisać nie wystarcz jace operacji kompresji i dekomresji BWT (`BWT` i `inverseBWT`).
    - [Huffman](#Huffman) programu [Huffman.c](./Huffman.c)
    - [LZ77_Huffman](#LZ77_Huffman) programu [LZ77_Huffman.c](./LZ77_Huffman.c)

- W nagłówku imie nazwisko, data
- Nazwa plika musi byc taka sama
- Formatowanie takie same, jak i w pliku.
- Z branch `develop` robimy PR w branch `develop`

## Termin wypełnienia zadania - 2023-06-20 23:59:59

## Opis

### BWT (Transformacja Burrowsa-Wheelera)

```bash
./BWT 
banana
 --> |annb^aa
 --> banana

milk
 --> |kmli^
 --> milk

bread white
 --> |ede^atrwhbi 
 --> bread white

TO BE OR NOT TO BE OR WANT TO BE OR NOT?
 --> |?OOORREEETTRTW   BBB  ATTT   NNOOONOO^   
 --> TO BE OR NOT TO BE OR WANT TO BE OR NOT?

SIX.FIVE.FOUR.THREE.TWO.ONE
 --> |EXEORENVER..TFSOW.FUH^..OITI
 --> SIX.FIVE.FOUR.THREE.TWO.ONE

^BBC|
 --> ERROR: String can't contain STX or ETX
 --> 

```

`BWT` :
```c
function BWT(input){
    append a special end-of-text marker to the input string
    create an empty list of rotations

    for (each rotation of the input string){
        append the rotation to the list of rotations
    }
    sort the list of rotations lexicographically

    set transformedString as an empty string
    for (each rotation in the sorted list of rotations){
        append the last character of the rotation to transformedString
    }
    return transformedString
}
```

####  `inverseBWT`
```c
function inverseBWT(transformedString){
    initialize a list of empty strings of the same length as transformedString

    for (i from 0 to the length of transformedString - 1) {
        insert transformedString at position i into the ith string of the list
    }
    sort the list of strings lexicographically

    find the string in the list that ends with the special end-of-text marker

    set originalString as the string without the end-of-text marker

    return originalString
}

```
