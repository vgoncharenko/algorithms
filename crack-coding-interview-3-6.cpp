//
// Created by Vitaliy on 2019-09-26.
//
#include <string>
#include <iostream>


//class CAnimal {
//public:
//    CAnimal(std::string &_name, int _order): name(_name), order(_order) {};
//    int setOrder(int _order)
//    {
//      order = _order;
//    }
//
//    int getOrder()
//    {
//      return order;
//    }
//    bool operator>(CAnimal a)
//    {
//      return order > a.getOrder();
//    }
//private:
//    std::string name {""};
//    int order {0};
//};
//
//class CCat : public CAnimal{};
//class CDog : public CAnimal{};
//
//class Shelter {
//    void enq(CCat *cat) {
//      enq(cat, cats);
//    }
//    void enq(CDog *dog) {
//      enq(dog, dogs);
//    }
//
//    void enq(CAnimal *animal, std::queue<CAnimal*> q)
//    {
//      animal->setOrder(this->order++);
//      q.push(animal);
//    }
//
//    CCat* deqCat()
//    {
//      return (CCat*)deq(cats);
//    }
//
//    CDog* deqDog()
//    {
//      return (CDog*)deq(dogs);
//    }
//
//    CAnimal* deq(std::queue<CAnimal*> q)
//    {
//      CAnimal *animal = q.front();
//      q.pop();
//      return animal;
//    }
//
//    CAnimal* deqAny()
//    {
//      if (dogs.front() > cats.front()) {
//        return deq(dogs);
//      } else {
//        return deq(cats);
//      }
//    }
//
//private:
//    std::queue<CAnimal*> cats, dogs;
//    int order = 0;
//};


class foo
{
public:
    foo(int _x,int _y,char _c);
    int get_x() const;
    int get_y() const;
    char get_c() const;
    template <std::size_t I>
    decltype(auto) get() const {
      if constexpr (I == 0) return get_x();
      else if constexpr (I == 1) return get_y();
      else if constexpr (I == 2) return get_c();
      else static_assert(I >= 0 && I < 3);
    }
private:
    int m_x = 1;
    int m_y =2;
    char m_c = 'a';
};

namespace std {

    template<>
    class tuple_size<foo> : public integral_constant<size_t, 3> {};

    template<size_t I>
    class std::tuple_element<I, foo> {
    public:
        using type = decltype (declval<foo>().get<I>());
    };

}

foo::foo(int _x,int _y,char _c):
        m_x(_x),
        m_y(_y),
        m_c(_c)
{

}

int foo::get_x() const
{
  return m_x;
}

int foo::get_y() const
{
  return m_y;
}

char foo::get_c() const
{
  return m_c;
}

template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
//concept Arithmetic = std:: is_arithmetic <T>::value;
T sum(T a)
{
  return a;
}

template <typename T, typename... Args>
//concept Arithmetic = std:: is_arithmetic <T>::value;
auto sum(T a, Args... args) -> std::common_type_t<T, Args...>
{
  return a + sum(args...);
}

void myfunction(){
  foo myfoo(2,3,5);
  auto [x1,y1,c] = myfoo;

  auto total = sum(x1, y1, c);
  std::cout<<"sum: "<<total<<std::endl;
}
