#include <cassert>
#include "Set.hpp"

int main() {
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

  //-----------------------------------------------
  std::cout << "===================================" << std::endl;

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

  //-----------------------------------------------
  std::cout << "===================================" << std::endl;

	b.__log__();
	a.__log__();

  auto first_odd_visitor_b = FirstOddVisitor<int>();
  b.accept(first_odd_visitor_b);
  auto result = first_odd_visitor_b.unwrap() == true ? std::to_string(*first_odd_visitor_b.unwrap()) : "None";
  std::cout << result << std::endl;

  auto first_odd_visitor_a = FirstOddVisitor<int>();
  a.accept(first_odd_visitor_a);
  result = first_odd_visitor_a.unwrap() == true ? std::to_string(*first_odd_visitor_a.unwrap()) : "None";
  std::cout << result << std::endl;

  a.remove(1);
  a.remove(5);

  first_odd_visitor_a = FirstOddVisitor<int>();
  a.accept(first_odd_visitor_a);
  result = first_odd_visitor_a.unwrap() == true ? std::to_string(*first_odd_visitor_a.unwrap()) : "None";
  std::cout << result << std::endl;

  //-----------------------------------------------
  std::cout << "===================================" << std::endl;

  for(auto item : a) std::cout << item << std::endl;

  //-----------------------------------------------
  std::cout << "===================================" << std::endl;

  for(auto item : b) std::cout << item << std::endl;
}


