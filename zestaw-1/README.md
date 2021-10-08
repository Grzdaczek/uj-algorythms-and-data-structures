### Zestaw 1
## Stos

Abstrakcyjny typ danych (Abstract data type, ADT), model matematyczny typu danych opisujący jego właściwości, a nie jego impolementację

Operacje:
- `Stack()` - Konstruktor tworzący pusty stos
- `push(a)` - dodawanie elementu `a` na stos
- `pop()` - zwraca ostatni elemnt stosu i usuwa go

Zabezpieczenia:
- Przed pop() na pustym stosie
- przed push(a) na pełnym stosie

# Implementacja tablicowa

Pola:
- `top` - wskaźnik na ostatni element stosu
- `data` - wskaźnik na tablicę danych

# Implementacja wskaźnikowa

Zawiera *węzły*, każdy znich przechowuje elemet T [szablon] oraz wskaźnik do poprzednioego *węzła*

Pop musi zwracać element a nie referencję do niego [w `std` nie zwraca nic]

Pola:
- `size` - aby funkcja `size()` mogła szybko zwrócić wielkośc stosu
- `top` - wskaźnik na ostatni *węzeł*

# Uwagi
Oby dwie implementacje, mają mieć identyczne API 

