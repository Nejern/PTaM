#include "singleton.h"
Singleton* Singleton::p_instance = nullptr;
SingletonDestroyer Singleton::destroyer;