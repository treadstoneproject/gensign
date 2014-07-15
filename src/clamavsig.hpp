#ifndef PARSER_CLAMAVSIG_HPP
#define PARSER_CLAMVASIG_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/mpl/print.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/struct.hpp>
#include <boost/fusion/include/nview.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <stdint.h>

namespace parser{



	struct meta_sigparse{
		std::string md5;
		std::string size;
		std::string virname;
	};



	class sig_parser{

	public:
		virtual bool parser_sig(const char * sig) = 0;
		
		virtual meta_sigparse get_parser_sig() const = 0;
		
		~sig_parser(){ };

	};

	//________________ Clamv Signature __________________________ //
	class clamav_sig : public sig_parser {

	public:

		typedef boost::fusion::result_of::as_nview<meta_sigparse, 0, 1, 2>::type
			md5_sig_virname;

		typedef std::string::const_iterator iterator_type;

		clamav_sig() : result_parse('\0'){ }

		virtual bool parser_sig(const char * sig);
		
		virtual meta_sigparse get_parser_sig()const { return meta_sigparse_; }
		
		//logic for drive class
		virtual bool filter_type(std::string const& sig) = 0;

		bool writeback(const char * sig);

		~clamav_sig() { delete result_parse; }

	protected:
		meta_sigparse meta_sigparse_;
		const char * result_parse;

	};

	//_________________ Clamav Daily Signature Parser ______________//
	class hdb_sig : public  clamav_sig{

	public:
		 bool filter_type(std::string const& sig);
	private:
		const char * sig_;
		boost::spirit::qi::rule<iterator_type, md5_sig_virname()> rule_parse_sig;
	};

}


#endif /* PARSER_CLAMVASIG_HPP */
