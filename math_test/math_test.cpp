// math_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	int res = RUN_ALL_TESTS();
	getchar();
	return res;
}

