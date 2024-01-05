######################################################################
# CMakeLists.txt generated for component MPC_Prediction
# Product type: static library
######################################################################
cmake_minimum_required(VERSION 3.12)
project(MPC_Prediction)
if(DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS} AND NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
endif()


######################################################################
## Path variables
######################################################################
get_filename_component(START_DIR ../../.. ABSOLUTE)
set(MATLAB_ROOT D:/MATLAB2023a CACHE PATH "")
if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(BUILDING_IN_SOURCE_DIR TRUE)
    set(BINARY_START_DIR "${START_DIR}")
else()
    set(BUILDING_IN_SOURCE_DIR FALSE)
    set(BINARY_START_DIR "${CMAKE_BINARY_DIR}")
endif()
if(WIN32 AND NOT MINGW)
    set(SYSLIB_PREFIX "lib")
else()
    set(SYSLIB_PREFIX "")
endif()

######################################################################
## System libraries
######################################################################
find_library(FOUND_LIBM m NO_SYSTEM_ENVIRONMENT_PATH PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}
    ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
find_library(FOUND_LIBSTDCXX stdc++ NO_SYSTEM_ENVIRONMENT_PATH PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}
    ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

######################################################################
## Target definition and commands
######################################################################
add_library(MPC_Prediction STATIC ${START_DIR}/codegen/lib/MPC_Prediction/rt_nonfinite.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/rtGetNaN.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/rtGetInf.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/MPC_Prediction_initialize.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/MPC_Prediction_terminate.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/MPC_Prediction.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xnrm2.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/factorQRE.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xzlarfg.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xzlarf.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/RemoveDependentIneq_.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/countsort.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/feasibleX0ForWorkingSet.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/computeQ_.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/setProblemType.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/computeFval.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/linearForm_.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/iterate.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/computeGrad_StoreHx.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xgemv.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/computeFval_ReuseHx.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xrotg.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/deleteColMoveEnd.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/compute_deltax.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/compute_lambda.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/addBoundToActiveSetMatrix_.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/checkStoppingAndUpdateFval.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/computeFirstOrderOpt.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/PresolveWorkingSet.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/xzgeqp3.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/factorQR.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/fullColLDL2_.cpp
    ${START_DIR}/codegen/lib/MPC_Prediction/MPC_Prediction_rtwutil.cpp)
set_target_properties(MPC_Prediction PROPERTIES
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_START_DIR}/codegen/lib/MPC_Prediction/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_START_DIR}/codegen/lib/MPC_Prediction/$<0:>"
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_START_DIR}/codegen/lib/MPC_Prediction/$<0:>")
target_compile_features(MPC_Prediction PUBLIC cxx_std_11)
target_compile_definitions(MPC_Prediction PRIVATE -DMODEL=MPC_Prediction)
target_include_directories(MPC_Prediction PUBLIC $<BUILD_INTERFACE:${START_DIR}/codegen/lib/MPC_Prediction>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/codegen/lib/MPC_Prediction>
    $<BUILD_INTERFACE:${START_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/extern/include>)
target_link_libraries(MPC_Prediction INTERFACE $<$<BOOL:${FOUND_LIBM}>:m>
    $<$<BOOL:${FOUND_LIBSTDCXX}>:stdc++>)


######################################################################
## Build success message
######################################################################
add_custom_command(TARGET MPC_Prediction POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "\\#\\#\\# Created library: $<TARGET_FILE:MPC_Prediction>")

######################################################################
## Call toolchain hook function if defined
######################################################################
if(COMMAND toolchain_target_hook)
    toolchain_target_hook(MPC_Prediction)
endif()
