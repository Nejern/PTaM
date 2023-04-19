#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
public:
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }

  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

protected:
  Singleton() {}
  ~Singleton() {}

private:
  class SingletonDestroyer {
  public:
    SingletonDestroyer(Singleton *p_instance) : p_instance(p_instance) {}
    ~SingletonDestroyer() { delete p_instance; }

  private:
    Singleton *p_instance;
  };

  friend class SingletonDestroyer;
};

#endif // SINGLETON_H
