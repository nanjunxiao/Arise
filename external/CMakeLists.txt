SET(MY_TOP_DIR "${CMAKE_SOURCE_DIR}")
SET(HTMLCXX_DIR "${CMAKE_SOURCE_DIR}/external/htmlcxx")
SET(HTMLTIDY_DIR "${CMAKE_SOURCE_DIR}/external/htmltidy")
INCLUDE_DIRECTORIES(${HTMLCXX_DIR} ${HTMLTIDY_DIR})

SET(htmlcxx_SRCS ${HTMLCXX_DIR}/Extensions.cc
		 ${HTMLCXX_DIR}/Node.cc  
		 ${HTMLCXX_DIR}/ParserDom.cc  
		 ${HTMLCXX_DIR}/ParserSax.cc
		 ${HTMLCXX_DIR}/Uri.cc
		 ${HTMLCXX_DIR}/utils.cc)

SET(htmltidy_SRCS ${HTMLTIDY_DIR}/access.c
		  ${HTMLTIDY_DIR}/alloc.c
		  ${HTMLTIDY_DIR}/attrask.c
		  ${HTMLTIDY_DIR}/attrdict.c
		  ${HTMLTIDY_DIR}/attrget.c
		  ${HTMLTIDY_DIR}/attrs.c
		  ${HTMLTIDY_DIR}/buffio.c
		  ${HTMLTIDY_DIR}/charsets.c
		  ${HTMLTIDY_DIR}/clean.c
		  ${HTMLTIDY_DIR}/config.c
		  ${HTMLTIDY_DIR}/entities.c
		  ${HTMLTIDY_DIR}/fileio.c
		  ${HTMLTIDY_DIR}/iconvtc.c
		  ${HTMLTIDY_DIR}/istack.c
		  ${HTMLTIDY_DIR}/lexer.c
		  ${HTMLTIDY_DIR}/localize.c
		  ${HTMLTIDY_DIR}/parser.c
		  ${HTMLTIDY_DIR}/pprint.c
		  ${HTMLTIDY_DIR}/streamio.c
		  ${HTMLTIDY_DIR}/tagask.c
		  ${HTMLTIDY_DIR}/tags.c
		  ${HTMLTIDY_DIR}/tidylib.c
		  ${HTMLTIDY_DIR}/tmbstr.c
		  ${HTMLTIDY_DIR}/utf8.c
		  ${HTMLTIDY_DIR}/win32tc.c)

ADD_LIBRARY(htmlcxx ${htmlcxx_SRCS})
ADD_LIBRARY(htmltidy ${htmltidy_SRCS})

INSTALL_TARGETS(/install/lib htmlcxx)
INSTALL_TARGETS(/install/lib htmltidy)

FILE(GLOB_RECURSE htmlcxx_header_files "${HTMLCXX_DIR}/*.h")

INSTALL(FILES ${htmlcxx_header_files} DESTINATION "install/include/htmlcxx")

FILE(GLOB_RECURSE htmlcxx_tcc_files "${HTMLCXX_DIR}/*.tcc")

INSTALL(FILES ${htmlcxx_tcc_files} DESTINATION "install/include/htmlcxx")

FILE(GLOB_RECURSE htmltidy_header_files "${HTMLTIDY_DIR}/*.h")

INSTALL(FILES ${htmltidy_header_files} DESTINATION "install/include/htmltidy")

FILE(GLOB_RECURSE htmltidy_tcc_files "${HTMLTIDY_DIR}/*.tcc")

INSTALL(FILES ${htmltidy_tcc_files} DESTINATION "install/include/htmltidy")
