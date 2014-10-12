#ifndef PARSER_CLAMAVSIG_HPP
#define PARSER_CLAMVASIG_HPP

/*
* Copyright 2014 Chatsiri Rattana.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*  Titles			                                          Authors	         Date
 * Support HDB extension signature of ClamAV              R.Chatsiri       15/07/2014
 */


#include <boost/config/warning_disable.hpp>
#include <boost/mpl/print.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/struct.hpp>
#include <boost/fusion/include/nview.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <stdint.h>

#include "logger/logging.hpp"
#include "utils/file_handler.hpp"
#include "utils/base/common.hpp"

namespace parser
{



    struct meta_sigparse {
				//meta_sigparse() : md5(""), size(""), virname(""){ }
				void clear(){  md5 = std::string(""); size = std::string(""); virname = std::string(""); }
        std::string md5;
        std::string size;
        std::string virname;
    };



    class sig_parser
    {

        public:
						virtual bool parse_file_sig(const char * file_path, std::vector<meta_sigparse*> * msig_vec) = 0; 
 
            virtual bool parser_sig(const char *sig) = 0;

            virtual meta_sigparse get_parser_sig() const = 0;

            ~sig_parser() { };

    };

    //________________ Clamv Signature __________________________ //
    class clamav_sig : public sig_parser
    {

        public:

            typedef boost::fusion::result_of::as_nview<meta_sigparse, 0, 1, 2>::type
            md5_sig_virname;

            typedef std::string::const_iterator iterator_type;

	     			typedef boost::shared_ptr<utils::meta_sig> msig_ptr;

            clamav_sig() : result_parse('\0') { }

						virtual bool parse_file_sig(const char *file_path, std::vector<meta_sigparse*> * msig_vec);


            virtual bool parser_sig(const char *sig);

            virtual meta_sigparse get_parser_sig()const {
								/*
								LOG(INFO) << "Msig md5 : " << meta_sigparse_.md5;
								LOG(INFO) << "Msig size  : " << meta_sigparse_.size;
					      LOG(INFO) << "Msig virname : " << meta_sigparse_.virname;
							  */
                return meta_sigparse_;
            }

            //logic for drive class
            virtual bool filter_type(std::string const& sig) = 0;

            bool writeback(const char *sig);

            ~clamav_sig() {
                delete result_parse;
            }

        protected:
            meta_sigparse meta_sigparse_;
            const char *result_parse;
				    utils::file_stream_handler<utils::common_filetype> fs_handler;
				private :
						//std::vector<msig_ptr> * msig_vec;
						//std::vector<meta_sigparse*>  msig_vec;					
    };

    //_________________ Clamav Daily Signature Parser ______________//
    class hdb_sig : public  clamav_sig
    {

        public:
            bool filter_type(std::string const& sig);
        private:
            const char *sig_;
            boost::spirit::qi::rule<iterator_type, md5_sig_virname()> rule_parse_sig;
    };

}


#endif /* PARSER_CLAMVASIG_HPP */
