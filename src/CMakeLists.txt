# src CMakeLists.txt
SET(MY_TOP_DIR "${CMAKE_SOURCE_DIR}")
SET(HTMLCXX_DIR "${CMAKE_SOURCE_DIR}/external/htmlcxx")
SET(HTMLTIDY_DIR "${CMAKE_SOURCE_DIR}/external/htmltidy")
SET(SRCS_DIR "${MY_TOP_DIR}/src")

INCLUDE_DIRECTORIES(${MY_TOP_DIR}/src ${MY_TOP_DIR}/external)

#library files
SET(Arise_SRCS 	${SRCS_DIR}/AttributeExtract.cpp
				${SRCS_DIR}/ExtracBase.cpp
				${SRCS_DIR}/ExtractWithoutWrapper.cpp
				${SRCS_DIR}/FunTools.cpp
				${SRCS_DIR}/Interface.cpp
				${SRCS_DIR}/NodeBase.cpp
				${SRCS_DIR}/Pretreat.cpp)

ADD_LIBRARY(Arise ${Arise_SRCS})

INSTALL_TARGETS(/install/lib Arise)

ADD_DEPENDENCIES(Arise htmlcxx htmltidy)

#header files
FILE(GLOB_RECURSE header_files "${SRCS_DIR}/*.h")

INSTALL(FILES ${header_files} DESTINATION install/include)

#utility files

ADD_EXECUTABLE(_Arise ${MY_TOP_DIR}/src/Demo.cpp)

TARGET_LINK_LIBRARIES(_Arise Arise htmlcxx htmltidy)

#TARGET_LINK_LIBRARIES(_AriseWithouWrapper AriseWithouWrapper)

INSTALL_TARGETS(/install/bin _Arise)

ADD_DEPENDENCIES(_Arise Arise htmlcxx htmltidy)

