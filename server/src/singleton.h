#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>

class Singleton;
class SingletonDestroyer {
 private:
  Singleton* p_instance;

 public:
  ~SingletonDestroyer() {
    delete p_instance;
    qDebug() << "~SingletonDestroyer";
  }
  void initialize(Singleton* p) { p_instance = p; }
};

class Singleton {
 private:
  static Singleton* p_instance;
  static SingletonDestroyer destroyer;

 protected:
  Singleton() { qDebug() << "Singleton()"; }
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  virtual ~Singleton() { qDebug() << "~Singleton()"; }
  friend class SingletonDestroyer;

 public:
  static Singleton* getInstance() {
    if (!p_instance) {
      p_instance = new Singleton();
      destroyer.initialize(p_instance);
    }
    return p_instance;
  }
};


#endif  // SINGLETON_H
