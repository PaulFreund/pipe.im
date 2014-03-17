//###################################################################################################
/*
    Copyright (c) since 2013 - Paul Freund 

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/
//###################################################################################################

module pipe.services.cmd;

//###################################################################################################

import nitro.textcom;
import pipe.services;
import std.stdio;
import std.conv;

//###################################################################################################

@Component struct MessageDebug { string message; }
@Component struct MessageWarning { string message; }
@Component struct MessageError { string message; }

//---------------------------------------------------------------------------------------------------

@System final class ServiceCmd(ECM) {

	//mixin AutoQuery;
	void run(ECM)(ECM ecm) {
        this._ecm = ecm;
		mixin AutoQueryMapper!ecm;
	}
	private ECM _ecm;


	bool handleDebug(ECM ecm, Entity e, Qry!MessageDebug c) {
		writeln("[Debug]" ~ c.message);
		return true;
	}

	bool query(Qry!MessageWarning c) {
		writeln("[Warning]" ~ c.message);
		return true;
	}

	bool query(Qry!MessageError c) {
		writeln("[Error]" ~ c.message);
		return true;
	}

	bool query(Qry!MessageWarning d, Qry!MessageError c) {
		writeln("[Error]" ~ c.message);
		return false;
	}

	bool socketUpdate(Qry!TextComSocketUpdate update) {
		import std.conv;
		writeln("[TextCom][" ~ update.socket ~ "]: " ~ to!string(update.status) ~ "(" ~ to!string(update.error) ~ ") - " ~ update.message);
		return true;
	}

	bool clientUpdate(Qry!TextComClientUpdate update) {
		import std.conv;
		writeln("[TextCom][" ~ update.socket ~ "][" ~ update.client ~ "]: " ~ to!string(update.status) ~ "(" ~ to!string(update.error) ~ ") - " ~ update.message);
		
        if(update.status == TextComStatus.Working)
            this._ecm.pushEntity(TextComOut(update.socket, [update.client], "Hello this is pipe speaking"));

        return true;
	}
	//void query(Qry!MessageError c, Qry!MessageWarning d) {
	//	writeln(" [Error]" ~ c.message);
	//	//return true;
	//}


}