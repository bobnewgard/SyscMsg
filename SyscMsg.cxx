/*
 * Copyright 2013-2021 Robert Newgard
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

#include <iomanip>
#include "SyscMsg.h"

namespace SyscMsg
{
    using namespace std;
    using namespace Chars;

    static ofstream     * log_stream = NULL;
    static sc_time_unit   unit_time;

    static string
    msg_handler_txt(const sc_report& rep)
    {
        double              double_now = rep.get_time().to_double();
        double              seconds_now = rep.get_time().to_seconds();
        double              now;
        string              unit;
        ostringstream       os;

        switch (SyscMsg::unit_time)
        {
            case SC_PS :
            {
                now  = double_now / 1000;
                unit = "ns";
                break;
            }
            case SC_FS :
            {
                now  = double_now * 1000;
                unit = "ns";
                break;
            }
            case SC_NS :
            {
                now  = double_now;
                unit = "ns";
                break;
            }
            default :
            {
                now  = seconds_now;
                unit = "sec";
                break;
            }
        }

        os << "[" << fixed << setprecision(6) << setw(16) << now << SP << unit << "]";
        os << rep.get_msg_type();

        if (*rep.get_msg())
        {
            os << CN << SP << rep.get_msg();
        }

        if (rep.get_severity() > SC_INFO)
        {
            os << NL << "In file" << SP << rep.get_file_name() << CM << SP;
            os << "line" << SP << rep.get_line_number();

            sc_simcontext * simc = sc_get_curr_simcontext();

            if (simc && sc_is_running())
            {
                const char* proc_name = rep.get_process_name();

                if (proc_name)
                {
                    os << NL << "In process" << SP << proc_name;
                }
            }
        }

        return os.str();
    }

    Msg::Msg(const char * arg)
    {
        msgid = string(arg);

        sc_report_handler::set_handler(&SyscMsg::Msg::msg_handler);

        if (sc_get_time_resolution() == sc_time(1, SC_PS))
        {
            SyscMsg::unit_time = SC_PS;
        }
        else if (sc_get_time_resolution() == sc_time(1, SC_FS))
        {
            SyscMsg::unit_time = SC_FS;
        }
        else if (sc_get_time_resolution() == sc_time(1, SC_NS))
        {
            SyscMsg::unit_time = SC_NS;
        }
        else
        {
            cout << "[WRN]" << SP << this->msgid << SP;
            cout << "Giving up trying to find time resolution; using seconds";
            cout << endl << flush;
            SyscMsg::unit_time = SC_SEC;
        }
    }

    Msg::Msg(const char * arg1, const char * arg2)
    {
        msgid = string(arg1);

        this->append_msgid(arg2);
    }

    Msg::Msg(const string & arg)
    {
        msgid = string(arg);
    }

    Msg::~Msg(void)
    {
        delete SyscMsg::log_stream;
    }

    // -------------------

    void
    Msg::append_msgid(const char * arg)
    {
        this->msgid.append(arg);
    }

    void
    Msg::append_msgid(const string & arg)
    {
        this->msgid.append(arg);
    }

    const char *
    Msg::get_str_c_msgid()
    {
        return this->msgid.c_str();
    }

    string &
    Msg::get_str_r_msgid()
    {
        return this->msgid;
    }

    // -------------------

    void
    Msg::cout_inf(const char * arg)
    {
        cout << "[INF]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cout_wrn(const char * arg)
    {
        cout << "[WRN]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cout_err(const char * arg)
    {
        cout << "[ERR]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cerr_inf(const char * arg)
    {
        cerr << "[INF]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    void
    Msg::cerr_wrn(const char * arg)
    {
        cerr << "[WRN]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    void
    Msg::cerr_err(const char * arg)
    {
        cerr << "[ERR]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    // -------------------

    void
    Msg::cout_inf(const string & arg)
    {
        cout << "[INF]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cout_wrn(const string & arg)
    {
        cout << "[WRN]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cout_err(const string & arg)
    {
        cout << "[ERR]" << SP << this->msgid << SP << arg;
        cout << endl << flush;
    }

    void
    Msg::cerr_inf(const string & arg)
    {
        cerr << "[INF]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    void
    Msg::cerr_wrn(const string & arg)
    {
        cerr << "[WRN]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    void
    Msg::cerr_err(const string & arg)
    {
        cerr << "[ERR]" << SP << this->msgid << SP << arg;
        cerr << endl << flush;
    }

    // -------------------


    void
    Msg::report_inf(const string & arg)
    {
        string tmp = "<INF>" + SP + this->get_str_r_msgid();

        SC_REPORT_INFO(tmp.c_str(), arg.c_str());
    }

    void
    Msg::report_wrn(const string & arg)
    {
        string tmp = "<WRN>" + SP + this->get_str_r_msgid();

        SC_REPORT_INFO(tmp.c_str(), arg.c_str());
    }

    void
    Msg::report_err(const string & arg)
    {
        string tmp = "<ERR>" + SP + this->get_str_r_msgid();

        SC_REPORT_INFO(tmp.c_str(), arg.c_str());
    }

    void
    Msg::msg_handler(const sc_report& arg_rep, const sc_actions& arg_act)
    {
        if (arg_act & SC_DISPLAY)
        {
            cout << SyscMsg::msg_handler_txt(arg_rep) << endl;
        }
        else if ((arg_act & SC_LOG) && sc_report_handler::get_log_file_name())
        {
            if (!SyscMsg::log_stream )
            {
                SyscMsg::log_stream = new ofstream(sc_report_handler::get_log_file_name()); // ios::trunc
            }

            *SyscMsg::log_stream << arg_rep.get_time() << CN + SP << SyscMsg::msg_handler_txt(arg_rep) << endl;
        }
        else
        {
            sc_report_handler::default_handler(arg_rep, arg_act);
        }
    }
}
