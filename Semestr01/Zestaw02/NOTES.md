# Zestaw 2
## Bufor cykliczny

Kolejka FIFO - *first in, first out*

Operacje:
- `void push(T a) / void enque(T a)` - wstawia `a` na koniec kolejki
- `T pop() / T deque()` - usuwa i zwraca element z początku kolejki
- `unsigned int size()` - zwraca licznę elementów w kolejce

## Implementacja tablicowa

Pola:
- `unsigned int head` - indeks najstarszego elementu
- `unsigned int tail` - indeks pod którym zostanie wstawiony następny nowy element
- `unsigned int size` - liczba elementów w kolejce

Na początku `head` i `tail` mają wartość 0. Można zrezygnować z pola `size` oraz pozostawić jedno wolne miejsce w kolejce aby w dalszym ciągu móc rozróżnić kolejkę zapełnioną od pustej.

Nie kożystać z `if`, lepiej wykożystać operator przypisania modulo. Lub jeszcze lepiej, dla kolejek o rozmiarze `N = 2^n`, posłużyć się operacjami bitowymi, tj. `tail = (tail+1) & (N-1)`. Tak zastosowana maska pozostawia tylko `n` najmłotrzych bitów `tail`.

## Implementacja wskaźnikowa

Pola:
- `Node* head`
- `Node* tail`
- `unsigned int size`

Lista jednokrotnie wiązana skierowana w stronę `tail`.

Szybka implementacja `pop()` wymaga przechowywania `Node* head`. Analogicznie w przypadku `push()`.
