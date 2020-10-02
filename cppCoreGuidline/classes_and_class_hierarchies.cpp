//
// Created by Vitaliy on 9/29/20.
//

// C.82: Don’t call virtual functions in constructors and destructors
// 1) what does it mean 'virtual'?
// 2) compilers allows to declare functions without defining them?
class Base {
public:
    virtual void f() = 0;
    virtual void g()
    {
      // client's code again save this. Only if I create class - the compiler will complain if this function doesn't exist
    }

    virtual void h() {
    }

    virtual ~Base() {
    }
};

class Derived : public Base {
public:
    void f() override {
      // that's good, at least client's code wouldn't work without defining f() here.
    }

    void g() override {
      Base::g();
    }

    void h() final {
      Base::h();
    }

    Derived()
    {
      // BAD: attempt to call an unimplemented virtual function
      f();

      // BAD: will call Derived::g, not dispatch further virtually
      g();

      // GOOD: explicitly state intent to call only the visible version
      Derived::g();

      // ok, no qualification needed, h is final
      h();
    }
};

void testC82() {
  Base *d = new Derived();
  d->g();
}


//C.87: Beware of == on base classes
// B’s comparison accepts conversions for its second operand, but not its first.
class B {
public:
    string name = "b";
    int number = 10;
//    virtual bool operator==(const B& a) const
//    {
//      return name == a.name && number == a.number;
//    }
    // ...
    virtual void f() {
      std::cout << "B::F()" << endl;
    }

    void f2() {
      std::cout << "B::F2()" << endl;
    }
};
class D : public B {
public:
    char character = 'd';
//    virtual bool operator==(const D& a) const
//    {
//      return name == a.name && number == a.number && character == a.character;
//    }
    // ...
    void f() override {
      std::cout << "D::F()" << endl;
    }

    void f2() {
      std::cout << "D::F2()" << endl;
    }
};

bool operator==(const B& a, const B& b) noexcept {
  return a.name == b.name && a.number == b.number;
}

bool operator==(const D& a, const D& b) noexcept {
  return a.name == b.name && a.number == b.number && a.character == b.character;
}

void testC83() {
  B b = B();
  D d = D();
  if (b == d) std::cout << "compare only name == a.name && number == a.number;\n";
  if (d == b) std::cout << "compare only name == a.name && number == a.number;\n"; // it cast both to bcd Type and call corresponding compare operator

  unique_ptr<B> bb = make_unique<D>();
  bb->f();  // call to D::F() because virtual
  bb->f2(); // call to B::F2() because non-virtual
}

