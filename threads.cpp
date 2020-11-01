//
// Created by Vitaliy on 2019-09-26.
//

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

std::mutex m1;

void thread_task(int i){
  try{
    while (i-->0) {
      m1.lock();
        std::cout << "Thread id: " << std::this_thread::get_id() << " i: " << i << std::endl;
      m1.unlock();
    }
  } catch (std::exception e) {
    m1.unlock();
  };

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::vector<std::thread> runThreads(int x) {
    std::vector<std::thread> v;
  for (int i = 0; i < x; ++i) {
      std::thread t {thread_task, i};
    v.push_back(move(t));
  }
    std::cout << "All threads runed!" << std::endl;

  return v;
}

void waitThreads(std::vector<std::thread> &&v) {
    for_each(v.begin(), v.end(), [](std::thread &t){t.join();});
}

void mainThreads() {
  int x = 10;
    std::cout << "Main function 1" << std::endl;
    std::vector<std::thread> &&v = runThreads(x);
    std::cout << "Main function 2" << std::endl;
  waitThreads(move(v));
    std::cout << "Main function 3" << std::endl;
}

