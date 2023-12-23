# CMakeList.txt : CMake project for LimeApiCmd, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("LimeApiCmd")

# Add source to this project's executable.
add_executable (LimeApiCmd "LimeApiCmd.cpp" "LimeApiCmd.h" "CmdParameter.cpp" "ControlFunctions.cpp")

target_include_directories(LimeApiCmd PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(LimeApiCmd PUBLIC ${PROJECT_SOURCE_DIR}/LimeSuite)

target_link_directories(LimeApiCmd PUBLIC ${PROJECT_SOURCE_DIR}/LimeSuite)
target_link_libraries(LimeApiCmd "LimeSuite.lib")

add_custom_command(TARGET LimeApiCmd
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy  ${PROJECT_SOURCE_DIR}/LimeSuite/LimeSuite.dll ${PROJECT_BINARY_DIR}/.
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LimeApiCmd PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
