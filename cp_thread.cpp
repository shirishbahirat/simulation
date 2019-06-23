#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

deque<int> q;

mutex mu;
condition_variable cond;

void producer() {
  int count = 10;
  while (count > 0) {
    unique_lock<mutex> locker(mu);
    q.push_front(count);
    locker.unlock();
    cond.notify_one();
    this_thread::sleep_for(chrono::seconds(1));
    count--;
  }
}

void consumer() {
  int data = 0;
  while (data != 1) {
    unique_lock<mutex> locker(mu);
    cond.wait(locker, []() { return !q.empty(); });
    data = q.back();
    q.pop_back();
    locker.unlock();
    cout << "consumer got data from producer: " << data << endl;
  }
}

int main(int argc, const char **argv) {
  thread prod(producer);
  thread cons(consumer);
  prod.join();
  cons.join();
  return 0;
}
