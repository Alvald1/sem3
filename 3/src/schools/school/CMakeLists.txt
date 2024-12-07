file(GLOB SOURCE *.cpp *.hpp)

# Цель для основной сборки
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE})

# Цель для отладочной сборки
target_sources(debug PRIVATE ${SOURCE})

# Цель для AddressSanitizer
target_sources(asan PRIVATE ${SOURCE})

# Цель для MemorySanitizer
target_sources(msan PRIVATE ${SOURCE})

# Цель для тестирования
target_sources(test_target PRIVATE ${SOURCE})