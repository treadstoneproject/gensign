#include "clamavsig.hpp"


using namespace parser;


//________________ Clamv Signature __________________________ //

BOOST_FUSION_ADAPT_STRUCT(
        meta_sigparse,
        (std::string, md5)
        (std::string, size)
        (std::string, virname)
)

bool clamav_sig::parser_sig(const char *sig)
{

    std::string sig_value(sig);

    if (filter_type(sig_value)) {
        //next process after parser completed.
        // Write data to database file.
        if (writeback(sig)) {

        }

        return true;
    }

    return false;
}

bool clamav_sig::writeback(const char *sig)
{
    return true;
}

//_________________ Clamav Daily-HDB  Signature Parser ______________//
bool hdb_sig::filter_type(std::string const& input)
{
    md5_sig_virname  sig_seq(boost::fusion::as_nview<0, 1, 2>(meta_sigparse_));

    //rule parser
    rule_parse_sig = *(boost::spirit::qi::char_ - ':') >> ":" >>  // MD5
                     *(boost::spirit::qi::char_ - ':') >> ":" >>  // Size file.
                     *(boost::spirit::qi::char_); // Virname

    iterator_type begin = input.begin();
    return boost::spirit::qi::parse(begin, input.end(), rule_parse_sig, sig_seq);
}
