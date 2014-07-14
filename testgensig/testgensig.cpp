// testgensig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/clamavsig.hpp"

TEST(GenerateSig, ClamavSig){
	const char * sig = "1cb223b8329ab8b4232:23235:Trojan-Smartor";
	parser::clamav_sig * clamsig = new parser::hdb_sig;
	ASSERT_EQ(clamsig->parser_sig(sig), true);
	parser::meta_sigparse msig = clamsig->get_parser_sig();
	EXPECT_EQ(msig.md5, "1cb223b8329ab8b4232");

}

int _tmain(int argc, _TCHAR* argv[])
{
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

