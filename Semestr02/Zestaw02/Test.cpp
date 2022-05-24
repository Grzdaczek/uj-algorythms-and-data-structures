#include <cassert>
#include "Set.hpp"

int main() {

/*
Nowa część testu:
Do zbioru A wstaw elementy wartość 5
Utwórz wizytatora dla zbioru A: v_A
A.Accept(v_A)
Wypisz sumę  policzoną przez v_A
E=A *B
Utwórz wizytatora dla zbioru E: v_E
E.Accept(v_E)
Wypisz sumę  policzoną przez v_E
Usuń wartość 1 z E i ponownie oblicz sumę elementów zbioru E korzystając z wizytatora
*/

  auto a = ArraySet(10);
	auto b = ArraySet(10);

	a.insert(0);
	a.insert(2);
	a.insert(4);
	a.insert(6);
	a.insert(8);

	b.insert(1);
	b.insert(3);
	b.insert(5);
	b.insert(7);
	b.insert(9);

	auto c = a + b;
	auto d = c - b;

	a.__log__();
	b.__log__();
	c.__log__();
	d.__log__();

	std::cout << (d == a) << std::endl;
	std::cout << (d <= a) << std::endl;
	std::cout << (c == b) << std::endl;
	std::cout << (b <= c) << std::endl;

  a.insert(1);

	std::cout << (d == a) << std::endl;
	std::cout << (d <= a) << std::endl;

  a.insert(5);
  auto sum_visitor_a = sumVisitor<int>();
  a.accept(sum_visitor_a);
  std::cout << sum_visitor_a.unwrap() << std::endl;

  auto e = a * b;
  auto sum_visitor_e = sumVisitor<int>();
  e.accept(sum_visitor_e);
  std::cout << sum_visitor_e.unwrap() << std::endl;

  e.remove(1);
  sum_visitor_e = sumVisitor<int>();
  e.accept(sum_visitor_e);
  std::cout << sum_visitor_e.unwrap() << std::endl;
}


