template<class T>
class AbstractList {
    struct Iterator;            // Zagnieżdżona klasa iteratora

    template<class U>           // Uniwersalna referencja U&&
    void push_front(U&& x);     // Wstawia element na początek listy
    
    template<class U>
    void push_back(U&& x);      // Wstawia element na koniec listy
    
    T pop_front();              // Usuwa element z początku listy i zwraca jego
                                // wartość lub wyrzuca wyjątek gdy lista jest pusta
    T pop_back();               // Usuwa element z końca listy i zwraca jego
                                // wartość lub wyrzuca wyjątek gdy lista jest pusta
    Iterator find(const T& x);  // Wyszukuje element o wartości`x`
                                // i zwraca jego pozycję
    Iterator erase(Iterator);   // Usuwa element wskazywany przez iterator
                                // i zwraca iterator do kolejnego elementu
    template<class U>Iterator insert(Iterator it, U&& x);   // Wstawia element x przed pozycję
                                                            // it i zwraca pozycję x
    int remove(const T& x);     // Usuwa wystąpienia x i zwraca ich liczbę   
};

