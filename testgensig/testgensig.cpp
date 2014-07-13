// testgensig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/clamavsig.hpp"

TEST(GenerateSig, ClamavSig){
	parser::sig_parser * parser = new parser::clamav_sig;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

