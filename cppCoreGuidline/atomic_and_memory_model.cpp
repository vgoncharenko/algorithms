//
// Created by Vitaliy on 10/12/20.
//

#include <atomic>
#include <thread>

struct MyAtomic {
    atomic<int64_t> x = 1;
    atomic<double> y = 1;
};

template<typename Callable, typename AssertFunction>
void atomicTest(Callable f, AssertFunction assertF, const int64_t expected, const std::string &testCaseName) {
  auto o = new MyAtomic();
  const int N = 50;

  // start threads
  vector<thread> v;
  for (int i = 0; i < N; ++i) {
    thread t{f, o};
    v.push_back(move(t));
  }

  // wait threads
  for_each(v.begin(), v.end(), [](thread &t) { t.join(); });

  // assert result
  if (assertF(o, expected)) {
    std::cout << "Test case '" << testCaseName << "' passed! \n";
  } else {
    std::cout << "Test case '" << testCaseName << "' failed! \n";
  }
  std::cout<< "x = " << o->x << "\ny = " << o->y << "\n\n";
}

//include <atomic>
//        std::atomic<int> num;
//void inc_relaxed() {
//  num.fetch_add(1, std::memory_order_relaxed);
//}
//
//int load_num() { return num; }            // Even seq_cst loads are free on x86
//void store_num(int val){ num = val; }
//void store_num_release(int val){
// num.store(val, std::memory_order_release);
//}
//
//# g++ 6.2 -O3, targeting x86-64 System V calling convention. (First argument in edi/rdi)
//inc_relaxed():
//  lock add DWORD PTR num[rip], 1      #### Even relaxed RMWs need a lock. There's no way to request just a single-instruction RMW with no lock, for synchronizing between a program and signal handler for example. :/ There is atomic_signal_fence for ordering, but nothing for RMW.
//ret
//
//inc_seq_cst():
//  lock add DWORD PTR num[rip], 1
//ret
//
//load_num():
//  mov eax, DWORD PTR num[rip]
//ret
//
//store_num(int):
//  mov DWORD PTR num[rip], edi
//  mfence                                     ##### seq_cst stores need an mfence
//ret
//
//store_num_release(int):
//  mov DWORD PTR num[rip], edi
//ret                                          ##### Release and weaker doesn't.
//
//store_num_relaxed(int):
//  mov DWORD PTR num[rip], edi
//ret
void testAtomic() {
  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 o->x++;
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->x == expected;
             },
             51,
             "o->x++"
             );

  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 o->x += 1;
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->x == expected;
             },
             51,
             "o->x += 1"
             );

  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 o->x = o->x + 1;
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->x == expected;
             },
             51,
             "o->x = o->x + 1"
             );

  // NOT COMPILABLE!!! most hardware vendors doesn't support.
//  atomicTest([](MyAtomic* o) {
//      this_thread::sleep_for(chrono::seconds(1));
//      o->x *= 2;
//  }, pow(2, 50), "o->x *= 2");

  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 o->x = o->x * 2;
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->x == expected;
             },
             pow(2, 50),
             "o->x = o->x * 2"
             );

  // NOT COMPILABLE!!! most hardware vendors doesn't support.
//  atomicTest([](MyAtomic* o) {
//      this_thread::sleep_for(chrono::seconds(1));
//      o->y++;
//  }, 51, "o->y++");

  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 o->y = o->y + 1;
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->y == expected;
             },
             51,
             "o->y = o->y + 1"
             );

  //https://stackoverflow.com/questions/45055402/atomic-double-floating-point-or-sse-avx-vector-load-store-on-x86-64
  atomicTest([](MyAtomic *o) {
                 this_thread::sleep_for(chrono::seconds(1));
                 double desired, expected = o->y.load(std::memory_order_relaxed);
                 do {
                   desired = expected + 1.0;
                   o->x++;
                 } while( !o->y.compare_exchange_weak(expected, desired) );
                 // if o->y == expected => o->y = desired and return true
                 // elseif o->y != expected => expected = o->y end return false
             },
             [](MyAtomic *o, const int64_t expected) {
                 return o->y == expected;
             },
             51,
             "o->y.exchange(o->y + 1)"
             );
}