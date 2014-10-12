#include "clamavsig.hpp"


using namespace parser;


//________________ Clamv Signature __________________________ //

BOOST_FUSION_ADAPT_STRUCT(
        meta_sigparse,
        (std::string, md5)
        (std::string, size)
        (std::string, virname)
)


bool clamav_sig::parse_file_sig(const char *file_path, std::vector<meta_sigparse*> * msig_vec)
{

    if(fs_handler.set_filepath(file_path)) {
        LOG(INFO)<<"File path : " << file_path;
    } else {
        LOG(INFO)<<"Cannot specific file path : " << file_path;
				return false;
    }

    if(fs_handler.file_read()) {
        LOG(INFO)<<"File can open";
    } else {
        LOG(INFO)<<"Cannot open file path : " << file_path;
				return false;
    }

    std::vector<std::string>  sig_strline;

    if(!fs_handler.read_all_line(sig_strline)) {
        LOG(INFO)<<"Signature is empty()";
				return false;
    }

    LOG(INFO)<<"Summary all records from signature file : " << sig_strline.size();
    LOG(INFO)<<"Warning signature not PE only. Please config msig->sig_type in production.";

    std::vector<std::string>::iterator iter_sig;
    for(iter_sig = sig_strline.begin();
            iter_sig != sig_strline.end();
            ++iter_sig) {
        std::string sig_value_str = *iter_sig;

        const char *sig_value = sig_value_str.c_str();

        if(filter_type(sig_value)) {


            std::string sig = meta_sigparse_.md5;
            std::string virname = meta_sigparse_.virname;

						msig_vec->push_back(new meta_sigparse);
						meta_sigparse * msig_parse = msig_vec->back();					
						msig_parse->md5 = sig;
						msig_parse->virname = virname;

        } else {
            LOG(INFO)<<" Record incorrect is : " << sig_value;
        }


    }//for

				for(int count = 0; count < msig_vec->size(); count++){
						  meta_sigparse * msig_parse = msig_vec->at(count);
						
						LOG(INFO)<<"Data : msig->sig: "<< msig_parse->md5;
				}

    LOG(INFO)<<"Recode of signatures are : " << msig_vec->size();
    return true;
}

bool clamav_sig::parser_sig(const char *sig)
{

    std::string sig_value(sig);

    if (filter_type(sig_value)) {
        //next process after parser completed.
        // Write data to database file.
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
    meta_sigparse_.clear();
    md5_sig_virname  sig_seq(boost::fusion::as_nview<0, 1, 2>(meta_sigparse_));

    //rule parser
    rule_parse_sig = *(boost::spirit::qi::char_ - ':') >> ":" >>  // MD5
            *(boost::spirit::qi::char_ - ':') >> ":" >>  // Size file.
            *(boost::spirit::qi::char_); // Virname

    iterator_type begin = input.begin();
    return boost::spirit::qi::parse(begin, input.end(), rule_parse_sig, sig_seq);
}
