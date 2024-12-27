# Создаем интерфейсную библиотеку для заголовков
add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем поддиректории
add_subdirectory(schools)
add_subdirectory(map)
add_subdirectory(ui)
add_subdirectory(managers)
add_subdirectory(queue)

# Собираем все исходные файлы и делаем доступными в родительском скопе
file(GLOB_RECURSE PROJECT_SOURCES *.cpp *.hpp)
set(PROJECT_SOURCES ${PROJECT_SOURCES} PARENT_SCOPE)
# Также экспортируем список исходников без main.cpp
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set(SOURCES ${PROJECT_SOURCES} PARENT_SCOPE)

# Объявляем исходный main
set(MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Создаем исполняемые цели
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(debug ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(asan ${MAIN_SOURCE} ${PROJECT_SOURCES})
add_executable(msan ${MAIN_SOURCE} ${PROJECT_SOURCES})

# Настраиваем выводные имена и директории
set_target_properties(${PROJECT_NAME} debug asan msan
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
set_target_properties(debug PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_debug)
set_target_properties(asan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_asan)
set_target_properties(msan PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_msan)

# Пример настройки опций компиляции
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_FLAGS})
target_compile_options(debug PRIVATE ${DEBUG_FLAGS})
target_compile_options(asan PRIVATE ${DEBUG_FLAGS} ${ASAN_FLAGS})
target_compile_options(msan PRIVATE ${DEBUG_FLAGS} ${MSAN_FLAGS})

# Линкуем project_includes и библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_libraries(debug PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_libraries(asan PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_options(asan PRIVATE ${ASAN_FLAGS})
target_link_libraries(msan PRIVATE ${CURSES_LIBRARIES} project_includes)
target_link_options(msan PRIVATE ${MSAN_FLAGS})

# Линкуем RapidJSON
target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_include_directories(debug PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_include_directories(asan PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_include_directories(msan PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

# Статический анализ
add_custom_target(static
    COMMAND clang-tidy
            -p ${CMAKE_BINARY_DIR}
            --quiet
            --header-filter='.*'
            --system-headers=false
            --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
            --use-color
            ${PROJECT_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running clang-tidy analysis"
)

# Valgrind
add_custom_target(valgrind
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target debug -j${N_JOBS}
    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all 
            --track-origins=yes --verbose ./${PROJECT_NAME}_debug
    COMMENT "Running Valgrind"
)