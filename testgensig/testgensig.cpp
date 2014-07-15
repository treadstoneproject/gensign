// testgensig.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32

#include "stdafx.h"

#endif

#include <iostream>

#include "gtest/gtest.h"
#include "gensign/clamavsig.hpp"

TEST(GenerateSig, ClamavSig){
	const char * sig = "1cb223b8329ab8b4232:23235:Trojan-Smartor";
	parser::clamav_sig * clamsig = new parser::hdb_sig;
	ASSERT_EQ(clamsig->parser_sig(sig), true);
	parser::meta_sigparse msig = clamsig->get_parser_sig();
	EXPECT_EQ(msig.md5, "1cb223b8329ab8b4232");
  EXPECT_EQ(msig.size,"23235");
  EXPECT_EQ(msig.virname, "Trojan-Smartor");
}



int _tmain(int argc, char  **argv)
{
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

