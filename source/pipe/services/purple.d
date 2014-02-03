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

module pipe.services.purple;

//###################################################################################################

import pipe.services;
import purple;

//###################################################################################################

@System final class ServicePurple(ECM) {
	PurpleClient _purple = null;

    this(ECM ecm) {
		ecm.pushEntity(MessageDebug("[Purple] Initializing"));

		this._purple = new PurpleClient();	   
		assert(this._purple !is null);	 
    }

    ~this() {
		this._purple.destroy();
	}

	void run(ECM)(ECM ecm) {
		mixin AutoQueryMapper!(ecm);

		//this._purple.process();

//        if(data.length != 0) {
//            auto e = ecs.createEntity();
//            ecs.addComponents(e, Message(data));    
//        }
	}


	//	}

        /*
            TODO: Replicate this with the new API    

            GList* lstNames = null;
            GList* iterPlugins = purple_plugins_get_protocols();
            int idxPlugin = 0;
            for(idxPlugin = 0; iterPlugins; iterPlugins = iterPlugins.next)
            {
            PurplePlugin *plugin = cast(PurplePlugin *)(iterPlugins.data);
            PurplePluginInfo *info = plugin.info;
            if(info && info.name)
            {
            printf("\t%d: %s\n".toStringz, idxPlugin++, info.name);
            lstNames = g_list_append(lstNames, info.id);
            }
            }

            bool debugAccount = true;
            string protocol = "prpl-jabber"; 
            string username = "pipetest@lvl3.org";
            string password = "333333"; 

            if(!debugAccount)
            {
            printf("Select the protocol [0-%d]: ".toStringz, idxPlugin - 1);
            int idxProtocol = to!int(strip(readln()));
            char* ptrProtocol = cast(char*)g_list_nth_data(lstNames, idxProtocol);
            protocol = to!string(ptrProtocol);

            printf("Username: ".toStringz);
            username = strip(readln());

            // Read password
            printf("Password: ".toStringz);
            password = strip(readln());
            }        

            PurpleAccount* account = purple_account_new(username.toStringz, protocol.toStringz);
            purple_account_set_password(account, password.toStringz);

            purple_account_set_enabled(account, _interfaceID.toStringz, true);

            PurpleSavedStatus* status = purple_savedstatus_new(null, PurpleStatusPrimitive.PURPLE_STATUS_AVAILABLE);
            purple_savedstatus_activate(status);
        */




}

//===================================================================================================

