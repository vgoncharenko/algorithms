//
// Created by Vitaliy on 2019-09-26.
//

#include <thread>

void thread_task(int i){
  this_thread::sleep_for(chrono::seconds(1));
  cout << "Thread id: " << this_thread::get_id() << " i: " << i << endl;
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

