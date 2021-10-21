# Zestaw 1
## Stos

-   ##### Omów przykłady zastosowania stosu?
	-  	Algorytmy (np. Algorytm Grahama)
	-  	Statyczne zarządzanie pamięcią (at compile time)
	-   Ewaluacja i parsowanie wyrażeń (np. ONP)
	-   Backtracking
-   ##### Dlaczego operacja `pop()` z `std::stack` nie zwraca wartości elementu?
	Ponieważ wartość elementu musiała by zostać skopiowana zanim została by usunięta ze stosu.
-   ##### Dlaczego operacja `pop()` z `std::stack` nie zwraca referencji do elementu?
	Ponieważ nie można zagwarantować istnienia elementu po usunięcu go ze stosu.
