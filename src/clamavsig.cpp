#include "clamavsig.hpp"

using namespace parser;

bool clamav_sig::parser_sig(const char * sig){

	if (filter_type(sig)){
		//next process after parser completed.
		// Write data to database file.
		if (writeback(sig)){

		}
	}

	return true;
}

const char * clamav_sig::get_parser_sig()const{
	return result_parse;
}

bool clamav_sig::writeback(const char * sig){
	return true;
}

bool clamav_sig::filter_type(const char * sig){
	return true;
}

bool daily_sig::filter_type(const char * sig){
	return true;
}