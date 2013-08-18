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

#include <SyscMsg.h>

using namespace std;
using namespace SyscMsg;
using namespace SyscMsg::Chars;

int sc_main(int argc, char **argv)
{
    Msg    * msg   = new Msg("Test:");
    Msg    * msg1  = new Msg("Test1:");
    Msg    * msg2  = new Msg(msg->get_str_c_msgid(), "Test2:");
    Msg    * msg3  = new Msg("Test3:");
    Msg    * msg4  = new Msg("Test4:");
    Msg    * msg5  = new Msg(msg->get_str_r_msgid() + "Test5:");
    Msg    * msg6  = new Msg(msg->get_str_r_msgid() + "Test6");

    string * str2  = new string("append:*(string*):");
    string   str3  = "append:" + msg->get_str_r_msgid() + "string:";
    string * str4  = new string("message *(string*)");

    msg2->append_msgid(*str2);
    msg3->append_msgid(str3);

    msg1->cout_inf("message cout_inf() char*");
    msg1->cout_wrn("message cout_wrn() char*");
    msg1->cout_err("message cout_err() char*");
    msg1->cerr_inf("message cerr_inf() char*");
    msg1->cerr_wrn("message cerr_wrn() char*");
    msg1->cerr_err("message cerr_err() char*");

    msg2->cout_inf("message cout_inf() char*");
    msg2->cout_wrn("message cout_wrn() char*");
    msg2->cout_err("message cout_err() char*");
    msg2->cerr_inf("message cerr_inf() char*");
    msg2->cerr_wrn("message cerr_wrn() char*");
    msg2->cerr_err("message cerr_err() char*");

    msg3->cout_inf("message cout_inf()" + SP + "string");
    msg3->cout_wrn("message cout_wrn()" + SP + "string");
    msg3->cout_err("message cout_err()" + SP + "string");
    msg3->cerr_inf("message cerr_inf()" + SP + "string");
    msg3->cerr_wrn("message cerr_wrn()" + SP + "string");
    msg3->cerr_err("message cerr_err()" + SP + "string");

    msg4->cout_inf(*str4);
    msg4->cout_wrn(*str4);
    msg4->cout_err(*str4);
    msg4->cerr_inf(*str4);
    msg4->cerr_wrn(*str4);
    msg4->cerr_err(*str4);

    msg5->cout_inf("message" + SP + msg->get_str_r_msgid() + SP + "string");
    msg5->cout_wrn("message" + SP + msg->get_str_r_msgid() + SP + "string");
    msg5->cout_err("message" + SP + msg->get_str_r_msgid() + SP + "string");
    msg5->cerr_inf("message" + SP + msg->get_str_r_msgid() + SP + "string");
    msg5->cerr_wrn("message" + SP + msg->get_str_r_msgid() + SP + "string");
    msg5->cerr_err("message" + SP + msg->get_str_r_msgid() + SP + "string");

    sc_report_handler::set_actions(SC_ERROR, SC_DISPLAY);

    msg6->report_inf("info test");
    msg6->report_wrn("warning test");
    msg6->report_err("error test");

    delete str4;
    delete str2;

    delete msg5;
    delete msg4;
    delete msg3;
    delete msg2;
    delete msg1;

    return 0;
}

