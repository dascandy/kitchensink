add_library(widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/calendar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/line_edit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/sliders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/tabdialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/calendar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/line_edit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/sliders.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/tabdialog.cpp
)

target_include_directories(widgets
  PUBLIC
    .
)
