#ifndef SINGLETON_MANAGER_HPP
#define SINGLETON_MANAGER_HPP

/**
 * @brief Manager class for handling all singleton instances
 * 
 * Utility class that provides static methods to initialize and destroy
 * all singleton instances in the application in the correct order.
 */
class SingletonManager {
  public:
    /**
     * @brief Initializes all singleton instances
     * 
     * Creates instances of all singleton managers in the correct order:
     * Schools, MapManager, EntityManager, DamageManager, SummonManager,
     * ActionManager, and GameManager.
     */
    static void initializeAll();

    /**
     * @brief Destroys all singleton instances
     * 
     * Destroys all singleton instances in the reverse order of their creation
     * to ensure proper cleanup.
     */
    static void destroyAll();

  private:
    SingletonManager() = delete;
};

#endif
