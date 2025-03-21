# Проверка версии Doxygen
find_package(Doxygen 1.9.0 REQUIRED)

# Определение путей исходников
set(DOC_SOURCES
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
)

# Основная конфигурация Doxygen
set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
set(DOXYGEN_PROJECT_BRIEF "Краткое описание проекта")
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_EXCLUDE_PATTERNS 
    */build/* 
    */test/*
    */.git/*
)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_FILE_PATTERNS *.hpp *.cpp *.h *.md)

# HTML конфигурация
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_HTML_OUTPUT "html")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(DOXYGEN_HTML_EXTRA_STYLESHEET "")
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_HTML_DYNAMIC_SECTIONS NO)
set(DOXYGEN_HTML_COLORSTYLE LIGHT)

# Расширенная конфигурация Doxygen
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_PACKAGE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_EXTRACT_LOCAL_CLASSES YES)
set(DOXYGEN_EXTRACT_LOCAL_METHODS YES)
set(DOXYGEN_EXTRACT_ANON_NSPACES YES)

# Включение дополнительной информации
set(DOXYGEN_SHOW_INCLUDE_FILES YES)
set(DOXYGEN_SHOW_NAMESPACES YES)
set(DOXYGEN_INLINE_INFO YES)
set(DOXYGEN_INLINE_INHERITED_MEMB YES)
set(DOXYGEN_INHERIT_DOCS YES)
set(DOXYGEN_FULL_PATH_NAMES YES)
set(DOXYGEN_RECURSIVE YES)

# Настройка вывода
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_REFERENCED_BY_RELATION YES)
set(DOXYGEN_REFERENCES_RELATION YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_GRAPHICAL_HIERARCHY YES)
set(DOXYGEN_DIRECTORY_GRAPH YES)
set(DOXYGEN_UML_LOOK YES)

# HTML настройки
set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
set(DOXYGEN_HTML_TIMESTAMP YES)
set(DOXYGEN_SEARCHENGINE YES)
set(DOXYGEN_GENERATE_DOCSET YES)

# Дополнительные настройки
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
set(DOXYGEN_GROUP_NESTED_COMPOUNDS YES)
set(DOXYGEN_SUBGROUPING YES)

# Генерация документации
doxygen_add_docs(doc
    ${DOC_SOURCES}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Generating HTML documentation with Doxygen"
)

# Цель для очистки
add_custom_target(clean_docs
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOXYGEN_OUTPUT_DIRECTORY}/html
    COMMENT "Cleaning HTML documentation files"
)