# Версия для линукса

cmake_minimum_required(VERSION 3.15)
project(IsntHard2)

set(CMAKE_CXX_STANDARD 17)

# Найти SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
set(SFML_STATIC_LIBRARIES TRUE)

# Найти libsndfile и FFTW
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(SNDFILE REQUIRED sndfile)
# pkg_check_modules(FFTW3F REQUIRED fftw3f)

# Найти OpenCL
find_package(OpenCL REQUIRED)
find_package(OpenMP REQUIRED)

# Исходные файлы, получить список можно скриптом src/scripts/getSources.sh, выполнять в корне проекта: sh src/scripts/getSources.sh
set(SOURCES
    cpp/Blocks/ElectricProcess.cpp
    cpp/EditorFeatures/EditorBuilding.cpp
    cpp/Engine/Physics.cpp
    cpp/Engine/Physics_processing.cpp
    cpp/Engine/Spawn.cpp
    cpp/LevelManager.cpp
    cpp/Loading.cpp
    cpp/Player.cpp
    cpp/SceneManager.cpp
    cpp/Scenes/Achievements.cpp
    cpp/Scenes/ContextMenu.cpp
    cpp/Scenes/Editor.cpp
    cpp/Scenes/EditorMenu.cpp
    cpp/Scenes/Game.cpp
    cpp/Scenes/Levels.cpp
    cpp/Scenes/Menu.cpp
    cpp/Scenes/Options.cpp
    cpp/Source.cpp
)

# Заголовочные файлы
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCL_INCLUDE_DIRS}  # Добавить пути к заголовкам OpenCL
)

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Привязываем OpenMP к цели
if(OpenMP_FOUND)
    message(STATUS "OpenMP поддержка включена")
endif()

# Подключить библиотеки
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    OpenMP::OpenMP_CXX
    ${OpenCL_LIBRARIES}     # Добавить библиотеки OpenCL
    m  # математическая библиотека для Linux
)

