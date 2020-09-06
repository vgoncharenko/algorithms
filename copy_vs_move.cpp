//
// Created by Vitaliy on 8/26/20.
//
#include <string>
#include <vector>
#include <iostream>
#include <memory>

template<typename T>
void draw(const T& s, std::ostream& out, size_t position) {
  out << std::string(position, ' ') << s << std::endl;
}
//       bad approach:
//void draw(const std::string& s, std::ostream& out, size_t position) {
//  out << std::string(position, ' ') << s << std::endl;
//}
//
//void draw(const int& n, std::ostream& out, size_t position) {
//  out << std::string(position, ' ') << n << std::endl;
//}


class object_copy {
public:
    template<typename T>
    object_copy(T s) : self_(new model_t<T>(std::move(s))) {
      std::cout << "move" << std::endl;
    }
//       bad approach:
//    object_copy(std::string s) : self_(new model_t(std::move(s))) {
//      std::cout << "move" << std::endl;
//    }
//    object_copy(int n) : self_(new int_model_t(std::move(n))) {
//      std::cout << "move" << std::endl;
//    }
    object_copy(const object_copy& o) : self_(o.self_->copy_()) {
      std::cout << "copy" << std::endl;
    }
    object_copy(object_copy&&) noexcept = default;

    object_copy& operator=(const object_copy& o)
    {
      object_copy tmp(o);
      *this = std::move(tmp);
      return *this;
    }

    object_copy& operator=(object_copy&&) noexcept = default;

    friend void draw (const object_copy& o, std::ostream& out, size_t position)
    {
      o.self_->draw_(out, position);
    }

private:
    struct base_model_t {
        virtual ~base_model_t() = default;
        virtual base_model_t* copy_() = 0;
        virtual void draw_(std::ostream& out, size_t position) const = 0;
    };

    template<typename T>
    struct model_t : base_model_t {

        explicit model_t(T s) : data(s) {
          //std::cout << "aaaa" << std::endl;
        };

        base_model_t* copy_() override {
          return new model_t<T>(*this);
        }

        void draw_(std::ostream& out, size_t position) const override
        {
          draw(data, out, position);
        }

        T data;
    };

//       bad approach:
//    struct string_model_t : base_model_t {
//        string_model_t(const std::string s) : data(s) { };
//        base_model_t* copy_() { return new string_model_t(*this); }
//        void draw_(std::ostream& out, size_t position) const
//        {
//          draw(data, out, position);
//        }
//
//        std::string data;
//    };
//
//    struct int_model_t : base_model_t {
//        int_model_t(const int n) : data(n) { };
//        base_model_t* copy_() { return new int_model_t(*this); }
//        void draw_(std::ostream& out, size_t position) const
//        {
//          draw(data, out, position);
//        }
//
//        int data;
//    };

    std::unique_ptr<base_model_t> self_;
};

object_copy func() {
  object_copy o = 5;
  return o;
};



class object_2 {
public:
    //object_2& operator=(object_2&) = delete;
    //object_2& operator=(object_2&&) = default;
    explicit object_2 (int n_) : n(n_) {}
    void print () {
      std::cout << n << std::endl;
    }
private:
    int n;
};

using object_2_container = std::vector<object_2>;
using object_copy_container = std::vector<object_copy>;

void draw(const object_copy_container& container, std::ostream& out, size_t position)
{
  out << std::string(position, ' ') << "<document>" << std::endl;
  for (const auto& item : container) {
    draw(item, out, position + 2);
  }
  out << std::string(position, ' ') << "</document>" << std::endl;
}

void copy_vs_move_test() {
  object_copy oc1 = 0; //move
  object_copy oc2 = 1; //move
  oc1 = func();        //move
  oc1 = oc2;           //copy
  oc1 = &oc2;          //move

  object_copy_container occ;
  occ.reserve(4);

  occ.emplace_back(0);       //move
  occ.emplace_back("asd");   //move
  occ.emplace_back(2);       //move
  occ.emplace_back("dsa");   //move

  draw(occ, cout, 0);

//  object_2_container oc;
//  oc.emplace_back(0);
//  oc.emplace_back(1);
//  oc.emplace_back(2);
//  oc.emplace_back(3);
//  std::for_each(oc.begin(), oc.end(), [](object_2 o){o.print();});
}
