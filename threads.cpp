//
// Created by Vitaliy on 2019-09-26.
//

#include <thread>
#include <mutex>

mutex m1;

void thread_task(int i){
  try{
    while (i-->0) {
      m1.lock();
      cout << "Thread id: " << this_thread::get_id() << " i: " << i << endl;
      m1.unlock();
    }
  } catch (exception e) {
    m1.unlock();
  };

  this_thread::sleep_for(chrono::seconds(1));
}

vector<thread> runThreads(int x) {
  vector<thread> v;
  for (int i = 0; i < x; ++i) {
    thread t {thread_task, i};
    v.push_back(move(t));
  }
  cout << "All threads runed!" << endl;

  return v;
}

void waitThreads(vector<thread> &&v) {
    for_each(v.begin(), v.end(), [](thread &t){t.join();});
}

void mainThreads() {
  int x = 10;
  cout << "Main function 1" << endl;
  vector<thread> &&v = runThreads(x);
  cout << "Main function 2" << endl;
  waitThreads(move(v));
  cout << "Main function 3" << endl;
}

