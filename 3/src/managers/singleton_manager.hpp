#ifndef SINGLETON_MANAGER_HPP
#define SINGLETON_MANAGER_HPP

class SingletonManager {
  public:
    static void initializeAll();
    static void destroyAll();

  private:
    SingletonManager() = delete;
};

#endif
