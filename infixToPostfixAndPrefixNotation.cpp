/*
//
// Created by Vitaliy on 10/18/20.
//
#include <stack>
#include <unordered_set>
#include <set>
#include <iterator>
#include <vector>

namespace infix {

#define Regular typename
#define Semiregular typename
#define TotallyOrdered typename
#define StrictWeakOrdering typename

#define InputIterator typename
#define ForwardIterator typename
#define BidirectionalIterator typename
#define RandomAccessIterator typename

#define IteratorBasis typename

    template<InputIterator I>
    using IteratorCategory = typename std::iterator_traits<I>::iterator_category;

    template<InputIterator I>
    using ValueType = typename std::iterator_traits<I>::value_type;

    template<InputIterator I>
    using DifferenceType = typename std::iterator_traits<I>::difference_type;

    template<InputIterator I>
    using Pointer = typename std::iterator_traits<I>::pointer;

    template<InputIterator I>
    using Reference = typename std::iterator_traits<I>::reference;

// Concept IteratorBasis
// - semiregular
// - state_type, value_type, reference, pointer, iterator_category
// - state_type is regular
// - deref() -> reference
// - increment() -> void
// - state() -> state_type
// For bidirectional iterators:
// - decrement()
// For random access iterators:
// - difference_type
// - offset(difference_type)
// - difference(y) -> difference_type

    template<IteratorBasis B>
    struct iterator {
        typedef typename B::state_type state_type;
        typedef typename B::value_type value_type;
        typedef typename B::difference_type difference_type;
        typedef typename B::reference reference;
        typedef typename B::pointer pointer;
        typedef typename B::iterator_category iterator_category;

        B basis;

        iterator() {}

        iterator(state_type x) : basis{x} {}

        template<typename T>
        //iterator(const T &x) : basis{x} {}

        state_type state() const { return basis.state(); }

        reference operator*() const { return basis.deref(); }

        pointer operator->() const { return &(**this); }

        iterator &operator++() {
          basis.increment();
          return *this;
        }

        iterator operator++(int) {
          iterator tmp = *this;
          ++*this;
          return tmp;
        }

        friend
        bool operator==(const iterator &x, const iterator &y) {
          return x.state() == y.state();
        }

        friend
        bool operator!=(const iterator &x, const iterator &y) {
          return !(x == y);
        }

        // for bidirectional iterator

        iterator &operator--() {
          basis.decrement();
          return *this;
        }

        iterator operator--(int) {
          iterator tmp = *this;
          --*this;
          return tmp;
        }

        // for random access iterator

        iterator &operator+=(difference_type i) {
          basis.offset(i);
          return *this;
        }

        iterator &operator-=(difference_type i) {
          *this += -i;
          return *this;
        }

        reference operator[](difference_type i) const {
          return *(*this + i);
        }

        friend
        difference_type operator-(const iterator &x, const iterator &y) {
          return x.basis.difference(y.basis);
        }

        iterator operator-(difference_type i) {
          return *this + (-i);
        }

        friend
        iterator operator+(iterator x, difference_type i) {
          return x += i;
        }

        friend
        iterator operator+(difference_type i, iterator x) {
          return x += i;
        }

        friend
        bool operator<(const iterator &x, const iterator &y) {
          return x - y < 0;
        }

        friend
        bool operator>(const iterator &x, const iterator &y) {
          return y < x;
        }

        friend
        bool operator<=(const iterator &x, const iterator &y) {
          return !(y < x);
        }

        friend
        bool operator>=(const iterator &x, const iterator &y) {
          return !(x < y);
        }
    };

    struct operator_item {
        char symbol;
        uint8_t rank;

        friend
        bool operator<(const operator_item &x, const operator_item &y) {
          return x.rank - y.rank < 0;
        }
    };

    template<InputIterator I>
// if x is of type I, then x->first is well formed
    struct operator_iterator_basis {
        I position;
        typedef decltype(position->rank) value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef DifferenceType<I> difference_type;
        typedef IteratorCategory<I> iterator_category;
        typedef I state_type;

        reference deref() const { return position->symbol; }

        void increment() { ++position; }

        // for bidirectional iterator
        void decrement() { --position; }

        // for random access iterator
        void offset(difference_type i) { position += i; }

        [[nodiscard]] difference_type difference(operator_iterator_basis y) const {
          return position - y.position;
        }

        [[nodiscard]] state_type state() const { return position; }
    };

    template<RandomAccessIterator I>
    using operator_iterator_t = iterator<operator_iterator_basis<I>>;

    std::vector<char> infixToPostfix(const std::vector<char> &input) {
      typedef operator_item P;
      const std::set <P> operations = {
              {'+', 2},
              {'-', 2},
              {'*', 1},
              {'/', 1}
      };
      std::stack<P> s;

      std::vector<char> result;
      for (auto it: input) {
        if (auto op = std::find(operator_iterator_t<P*>(begin(operations)), operator_iterator_t<P*>(end(operations)), it);
                op == operations.end()) {
          result.push_back(it);
        } else {
          while (!s.empty() && *op <= s.top().rank) {
            result.push_back(s.top().symbol);
            s.pop();
          }
          //s.push(*op);
        }
      }

      while (!s.empty()) {
        result.push_back(s.top().symbol);
        s.pop();
      }

      return result;
    }

    void testInfixToPostfix() {
        std::vector<char> input,
              expected,
              result;

      input = {'a', '+', 'b', '-', 'd', '*', 'f'};
      expected = {'a', 'b', '+', 'd', 'f', '*', '-'};
      result = infixToPostfix(input);
      assert(expected == result);
    }
}*/
