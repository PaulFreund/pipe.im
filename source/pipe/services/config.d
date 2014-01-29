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

module pipe.services.config;

//###################################################################################################

import pipe.services;
import std.stdio;
import std.file;
import vibe.data.json;

//###################################################################################################

string value(Json object, string key) {

    if(object.type == Json.Type.object) {
        if(auto child = key in object.get!(Json[string]))
            object = *child;
    }

    if(object.type == Json.Type.string)
        return object.get!string;

    return null;
}

//===================================================================================================

@Component struct Settings {
    string name;
    bool debug_;
}

@Component struct User {
    string id;
    string password;
    bool admin;
    Service[] services;
}

@Component struct Service {
    string user;
    string type;
    string id;
    string password;
    string uri;
}





//===================================================================================================

@System final class ServiceConfig(ECM) {
private:
    const string configName = "config.json";
public:
    Json config;

    mixin AutoQuery;

    this(ECM ecm) {
        writeln("CONFIG INIT");

		ecm.pushEntity(DebugMessage("DebugMsg"), WarningMessage("WarningMsg"));

        if(!exists(this.configName) ) {
            writeln("No config.json found. exiting");
            return;
        }

        string configData = cast(string)read(this.configName);
        this.config = parseJson(configData);

        if(this.config.type != Json.Type.object) {
            writeln("Invalid config file");
            return;
        }

        if(string name = this.config.value("name"))
            writeln("Using config \"" ~ name ~ "\"");

        auto accountsNode = this.config["accounts"];
        if(accountsNode.type == Json.Type.array) {
            foreach(Json account; accountsNode.get!(Json[])) {
                if(account.type == Json.Type.object) {
                    writeln("Name: " ~ account.value("name"));
                    writeln("Type: " ~ account.value("type"));
                    writeln("Username: " ~ account.value("username"));
                    writeln("Password: " ~ account.value("password"));
                }
            }
        }
    } 
}
