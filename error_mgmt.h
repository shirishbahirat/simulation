#pragma once

class error_mgmt_interface {
public:
  error_mgmt_interface();

  virtual void DoSomething();

private:
  int x;
};
