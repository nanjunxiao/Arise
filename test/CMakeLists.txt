#test CMakeLists.txt
SET(MY_TOP_DIR "${CMAKE_SOURCE_DIR}")

ADD_EXECUTABLE(_cmp ${MY_TOP_DIR}/test/cmp.c)

#test html file with baidu pages

ADD_TEST(test_Arise_1 ../src/_Arise "${MY_TOP_DIR}/test/baidubeijingxiaochi.htm" "0" "${MY_TOP_DIR}/test/baidubeijingxiaochi.out")
ADD_TEST(test_Compare_1 _cmp "${MY_TOP_DIR}/test/baidubeijingxiaochi.out"  "${MY_TOP_DIR}/test/baidubeijingxiaochi.refwin")
SET_TESTS_PROPERTIES(test_Compare_1 PROPERTIES DEPENDS test_Arise_1 PASS_REGULAR_EXPRESSION "OK")

#test html file with google pages
ADD_TEST(test_Arise_2 ../src/_Arise "${MY_TOP_DIR}/test/googlebeijingxiaochi.htm" "0" "${MY_TOP_DIR}/test/googlebeijingxiaochi.out")
ADD_TEST(test_Compare_2 _cmp "${MY_TOP_DIR}/test/googlebeijingxiaochi.out" "${MY_TOP_DIR}/test/googlebeijingxiaochi.refwin")
SET_TESTS_PROPERTIES(test_Compare_2 PROPERTIES DEPENDS test_Arise_2 PASS_REGULAR_EXPRESSION "OK")
