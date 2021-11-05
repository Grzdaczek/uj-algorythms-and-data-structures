# Zestaw 3

## Lista z dowiązaniami

Do wykonania implementacja wskaźnikowa listy. Metody:

```C++
class List {
    void push_front(int x);     // Dołącza element na początek listy
    int pop_front();            // Usuwa i zwraca element z początku listy
    void push_back(int x);      // Dołącza element na koniec listyint 
    pop_back();                 // Usuwa i zwraca element z końca listy
    int size();                 // Zwraca liczbę elementów w liście
    bool empty();               // Zwraca true gdy lista jest pusta
    void clear();               // Czyści listę
    int find(int x);            // Zwraca pozycję pierwszego elementu o wartości x
    int erase(int i);           // Usuwa i zwraca element na pozycji i
    void insert(int i, int x);  // Wstawia element x przed pozycję i
    int remove(int x);          // Usuwa wystąpienia x i zwraca ich liczbę
};
```

Urzycie węzła terminującego listę: `guard`. Tworzy to cykliczną strukturę i umożliwia pominięcie instrukcji warónkowych podczas wstawiania na koniec i początek listy.

Należy zaimplementować dwukierunkowy iterator. Ma to być struct zawierający pole `Node* ptr` wskazujące na element listy. Iterator przeciąża operatory:
- `++`
- `--`
- `==`
- `!=`
