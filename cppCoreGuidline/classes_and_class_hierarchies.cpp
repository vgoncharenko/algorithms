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
    std::string name = "b";
    int number = 10;
//    virtual bool operator==(const B& a) const
//    {
//      return name == a.name && number == a.number;
//    }
    // ...
    virtual void f() {
      std::cout << "B::F()" << std::endl;
    }

    void f2() {
      std::cout << "B::F2()" << std::endl;
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
      std::cout << "D::F()" << std::endl;
    }

    void f2() {
      std::cout << "D::F2()" << std::endl;
    }
};

class NotDerivedFromBase {
public:
    char character = 'd';
//    virtual bool operator==(const D& a) const
//    {
//      return name == a.name && number == a.number && character == a.character;
//    }
    // ...
    virtual void f() {
      std::cout << "NotDerivedFromBase::F()" << std::endl;
    }
};

class DerivedFromNotDerivedFromBase : public NotDerivedFromBase, public B {
    void f() override {
      std::cout << "DerivedFromNotDerivedFromBase::F()" << std::endl;
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

    std::unique_ptr<B> bb = std::make_unique<D>();
  bb->f();  // call to D::F() because virtual
  bb->f2(); // call to B::F2() because non-virtual
}


void testC147_f(NotDerivedFromBase a) { // +slice
  try {
    B base = dynamic_cast<B&>(a);
  } catch (std::exception e) {
    std::cout << "C.147: Use dynamic_cast to a reference type when failure to find the required class is considered an error\n";
  }
}

void testC147() {
  DerivedFromNotDerivedFromBase notDerivedFromBase = DerivedFromNotDerivedFromBase();
  testC147_f(notDerivedFromBase); // +slice
}

void testC148_f(NotDerivedFromBase* const p) {
  auto base = dynamic_cast<B*>(p);
  if (base == nullptr) {
    std::cout << "C.148: Use dynamic_cast to a pointer type when failure to find the required class is considered a valid alternative\n";
  }
}

void testC148() {
  NotDerivedFromBase *notDerivedFromBaseP = new NotDerivedFromBase();
  testC148_f(notDerivedFromBaseP);
}

void testC166() {
  int x = 10;
  int *y = &x; // pointer
  int &z = x;  // ref
  int g = z;   // copy

  *y += 1;
  std::cout << "x=" << x << "; *y=" << *y << "; z=" << z << "; g=" << g << std::endl;

  z += 1;
  std::cout << "x=" << x << "; *y=" << *y << "; z=" << z << "; g=" << g << std::endl;

  g += 1;
  std::cout << "x=" << x << "; *y=" << *y << "; z=" << z << "; g=" << g << std::endl;
}
