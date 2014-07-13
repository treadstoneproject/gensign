#ifndef PARSER_CLAMAVSIG_HPP
#define PARSER_CLAMVASIG_HPP

#include <iostream>
#include <string>

namespace parser{

	class sig_parser{

	public:
		virtual bool parser_sig(const char * sig) = 0;

		virtual const char * get_parser_sig() const = 0;

		~sig_parser();

	};

	//________________ Clamv Signature __________________________ //
	class clamav_sig : public sig_parser {

	public:

		clamav_sig() : result_parse('\0'){ }

		virtual bool parser_sig(const char * sig);

		virtual const char * get_parser_sig() const;

		//logic for drive class
		bool filter_type(const char * sig);

		bool writeback(const char * sig);


	protected:

		const char * result_parse;

	};

	//_________________ Clamav Daily Signature Parser ______________//
	class daily_sig : public  clamav_sig{

	public:
		virtual bool filter_type(const char * sig);
	private:
		const char * sig_;
	};

}


#endif /* PARSER_CLAMVASIG_HPP */
