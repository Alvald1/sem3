# Создаем интерфейсную библиотеку для заголовков
add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем поддиректории
add_subdirectory(schools)
add_subdirectory(map)
add_subdirectory(ui)
add_subdirectory(managers)
add_subdirectory(queue)

# Собираем все исходные файлы
set(PROJECT_SOURCES "")
file(GLOB_RECURSE PROJECT_SOURCES *.cpp *.hpp)

# Объявляем исходный main
set(MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Создаем исполняемые цели
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(debug ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(asan ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(msan ${MAIN_SOURCE} ${PROJECT_SOURCES})

# Пример настройки опций компиляции
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_FLAGS})
target_compile_options(debug PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS})
target_compile_options(asan PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS} ${ASAN_FLAGS})
target_compile_options(msan PRIVATE ${COMMON_COMPILE_FLAGS} ${DEBUG_FLAGS} ${MSAN_FLAGS})

# Линкуем project_includes и библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_libraries(debug PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_libraries(asan PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_options(asan PRIVATE ${ASAN_FLAGS})
target_link_libraries(msan PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_options(msan PRIVATE ${MSAN_FLAGS})

# Настраиваем выводные имена
set_target_properties(debug PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)
set_target_properties(asan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)
set_target_properties(msan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)