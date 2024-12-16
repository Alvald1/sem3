# Проверка версии Doxygen
find_package(Doxygen 1.9.0 REQUIRED)

# Check for required LaTeX packages
find_program(PDFLATEX_COMPILER pdflatex)
if(NOT PDFLATEX_COMPILER)
    message(FATAL_ERROR "pdflatex not found! Please install:
    sudo apt-get install texlive-base texlive-lang-cyrillic texlive-fonts-recommended texlive-latex-extra")
endif()

# Create header.tex if it doesn't exist
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/header.tex)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/header.tex
"\\usepackage[T2A]{fontenc}
\\usepackage[utf8]{inputenc}
\\usepackage[english,russian]{babel}
\\usepackage{amsmath}
\\usepackage{amsfonts}
\\usepackage{amssymb}")
endif()

# Определение путей исходников
set(DOC_SOURCES
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
)

# Check if LaTeX header exists, if not, don't use it
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/header.tex)
    set(DOXYGEN_LATEX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/header.tex")
endif()

# Конфигурация Doxygen
set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
set(DOXYGEN_PROJECT_BRIEF "Краткое описание проекта")
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_ALPHABETICAL_INDEX NO)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_CASE_SENSE_NAMES NO)
set(DOXYGEN_CLASS_DIAGRAMS YES)
set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
set(DOXYGEN_EXCLUDE_PATTERNS 
    */build/* 
    */test/*
    */.git/*
)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_LOCAL_CLASSES NO)
set(DOXYGEN_FILE_PATTERNS *.hpp *.cpp *.h *.md)
set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_LATEX_OUTPUT "latex")
set(DOXYGEN_USE_PDFLATEX YES)
set(DOXYGEN_PDF_HYPERLINKS YES)
set(DOXYGEN_LATEX_BATCHMODE YES)
set(DOXYGEN_LATEX_BIB_STYLE "plain")
set(DOXYGEN_COMPACT_LATEX YES)
set(DOXYGEN_HIDE_FRIEND_COMPOUNDS YES)
set(DOXYGEN_HIDE_IN_BODY_DOCS YES)
set(DOXYGEN_HIDE_UNDOC_CLASSES YES)
set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
set(DOXYGEN_QUIET YES)
set(DOXYGEN_RECURSIVE YES)
set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
set(DOXYGEN_SORT_MEMBER_DOCS NO)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_STRIP_CODE_COMMENTS NO)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

# Update Doxygen configuration
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_USE_PDFLATEX YES)
set(DOXYGEN_LATEX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/header.tex")
set(DOXYGEN_LATEX_EXTRA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/header.tex")
set(DOXYGEN_LATEX_CMD_NAME "pdflatex")
set(DOXYGEN_LATEX_BATCHMODE YES)
set(DOXYGEN_LATEX_TIMESTAMP NO)
set(DOXYGEN_LATEX_EMOJI_DIRECTORY "")

# Генерация документации
doxygen_add_docs(doxygen_doc
    ${DOC_SOURCES}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Generating LaTeX documentation with Doxygen"
)

# Add custom command to build PDF
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    DEPENDS doxygen_doc
    COMMENT "Generating PDF documentation"
)

# Main documentation target that generates PDF
add_custom_target(doc ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_documentation.pdf
    COMMENT "Copying final PDF documentation"
)

# Цель для очистки документации
add_custom_target(clean_docs
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOXYGEN_OUTPUT_DIRECTORY}/latex
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_documentation.pdf
    COMMENT "Cleaning documentation files"
)