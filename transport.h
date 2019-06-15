#pragma once

class transport_interface {
public:
  transport_interface();

  virtual void DoSomething();

private:
  int x;
};
