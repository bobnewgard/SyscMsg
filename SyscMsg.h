/*
 * Copyright 2013 Robert Newgard
 *
 * This file is part of SyscMsg.
 *
 * SyscMsg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SyscMsg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SyscMsg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SYSCMSG_H_
    #define _SYSCMSG_H_

    #include <systemc.h>
    #include <string>
    #include <iostream>

    namespace SyscMsg
    {
        using std::string;

        namespace Chars
        {
            const string SP = "\x20";
            const string CM = ",";
            const string CN = ":";
            const string NL = "\n";
            const string SQ = "\'";
            const string DQ = "\"";
            const string TB = "\t";
        }

        class Msg
        {
            private:
                string       msgid;

                static void  msg_handler(const sc_report&, const sc_actions&);

            public:
                Msg(const char*);
                Msg(const char*, const char*);
                Msg(const string&);
                ~Msg(void);

                const char * get_str_c_msgid(void);
                string     & get_str_r_msgid(void);
                void         append_msgid(const char*);
                void         append_msgid(const string&);

                void         cout_inf(const char *);
                void         cout_wrn(const char *);
                void         cout_err(const char *);
                void         cerr_inf(const char *);
                void         cerr_wrn(const char *);
                void         cerr_err(const char *);

                void         cout_inf(const string &);
                void         cout_wrn(const string &);
                void         cout_err(const string &);
                void         cerr_inf(const string &);
                void         cerr_wrn(const string &);
                void         cerr_err(const string &);

                void         report_inf(const string &);
                void         report_wrn(const string &);
                void         report_err(const string &);
        };
    }
#endif
