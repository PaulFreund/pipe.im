//###################################################################################################
/*
    Copyright (c) since 2013 - Felix 'Zoadian' Hufnagel, Paul Freund 

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

module nitro.ecs;

//###################################################################################################

import std.algorithm : canFind, remove, SwapStrategy, countUntil;
import std.typecons : Typedef, Unique;
import stdx.typetuple : Sorted, Filter, staticMap, TypeTuple, allSatisfy, NoDuplicates, staticIndexOf;	  
import std.traits : hasMember;
import std.stdio : writeln;

//###################################################################################################

auto query(T, CS...)(Entity e, T ecs, CS cs) { return ecs.query!(CS)(e, cs); }

//==============================================================================
///
void _removeInplaceUnstable(T)(ref T[] ts, T v) {
	size_t l = ts.length;
	for(size_t i = 0; i < l; ++i) {
		if(ts[i] == v) {
			ts[i] = ts[--l];
		}
	}
	ts.length = l;
}


//==============================================================================
/// 
struct Query(TYPES...) {
private:
	alias _Types = Sorted!("a<b", TYPES);
}

private void _isQueryImpl(T...)(Query!(T) n) {}
enum isQuery(T...)  = is(typeof(_isQueryImpl(T.init)));


//==============================================================================
/// 
alias Entity = Typedef!ulong;



//==============================================================================
/// 
mixin template EntityComponentManager(QUERIES...) if(allSatisfy!(isQuery, QUERIES)) {	
	private alias _Types(Q) = Q._Types;
	private alias _MapType(T) = T[Entity];
	private alias FixQuery(Q) = Query!(Sorted!("a<b", _Types!Q));
	private alias U_QUERIES = NoDuplicates!(staticMap!(FixQuery, QUERIES));
	private alias U_TYPES = NoDuplicates!(staticMap!(_Types, U_QUERIES));
	private alias U_MAP_TYPE = staticMap!(_MapType, U_TYPES);			 

	Entity _cnt = 1;
	Entity[] _entities;
	Entity[][U_QUERIES.length] _queries;	 		 
	U_MAP_TYPE _data;	 				

	pragma(msg, "");
	pragma(msg, "\t", "==================================");
	pragma(msg, "\t", "Managed Components:");
	pragma(msg, "\t", U_TYPES);		   
	pragma(msg, "\t", "----------------------------------");
	pragma(msg, "\t", "Managed Queries:");
	pragma(msg, "\t", U_QUERIES);	
	pragma(msg, "\t", "----------------------------------");

public:		
	///
	enum hasQuery(T) = staticIndexOf!(T, U_QUERIES) != -1;		

	///
	enum hasComponent(T) = staticIndexOf!(T, U_TYPES) != -1;

public:		 
	///
	Entity createEntity() {
		_entities ~= _cnt;
		return _cnt++;
	}

	///
	void removeEntity(Entity e) {
		_entities._removeInplaceUnstable(e);   

		foreach(ref a; _queries) {
			a._removeInplaceUnstable(e);
		}

		foreach(ref a; _data) {
			a.remove(e);
		}

		//TODO:	update all components with references to entity e
	}

	///
	void addComponents(CS...)(Entity entity, CS cs) if(allSatisfy!(hasComponent, CS)){
		static assert(CS.length == (NoDuplicates!(CS)).length, "can't add twice");	 
		// Assign Data
		foreach(t; cs)
		{
			alias IDX = staticIndexOf!(typeof(t), U_TYPES);
			static assert(IDX != -1, "type " ~ typeof(t).stringof ~ " no managed");
			_data[IDX][entity] = t; 
		}									  

		// Make Available for Queries
		foreach(i, Q; U_QUERIES) {
			foreach(C; CS) {				
				enum IDX = staticIndexOf!(C, _Types!(Q));	  
				static if(IDX != -1) {			
					//pragma(msg, IDX, "   ",  T, "    ", _Types!(Q));	  
					if(!_queries[i].canFind(entity)) {
						_queries[i] ~= entity;
					}
					break;
				}
			}
		}
	}

	///
	auto query(C...)() if(hasQuery!(Query!(Sorted!("a<b", C)))) {
		alias IDX = staticIndexOf!(Query!(Sorted!("a<b", C)), U_QUERIES);
		static assert(IDX != -1, "not a valid query");	   
		return _queries[IDX]; 
	}	 

	///
	auto getComponent(C)(Entity entity) if(hasComponent!C) {	  
		alias IDX = staticIndexOf!(C, U_TYPES);
		static assert(IDX != -1, "not a valid query");	
		static assert(IDX < _data.length, "not a valid querty : 2");
		//assert((entity in _data[IDX]) != null, "error entity does not have this component");
		return entity in _data[IDX];
	}

	///
	auto getAllComponents(C)() if(hasComponent!C) {	  
		alias IDX = staticIndexOf!(C, U_TYPES);
		static assert(IDX != -1, "not a valid query");	
		static assert(IDX < _data.length, "not a valid querty : 2");
		//assert((entity in _data[IDX]) != null, "error entity does not have this component");
		return _data[IDX].byValue;
	}

	///  
	void removeComponents(CS...)(Entity entity) if(allSatisfy!(hasComponent, CS)) {
		foreach(C; CS) {
			_removeComponent!(C)(entity);
		}
	}

private:
	void _removeComponent(C)(Entity entity) if(hasComponent!C) {
		foreach(i, Q; U_QUERIES) {
			enum IDX = staticIndexOf!(C, _Types!(Q));	
			static if(IDX != -1) {	
				auto idx = _queries[i].countUntil(entity);
				if(idx != -1) {
					_queries[i][idx] = _queries[i][$-1];
					_queries[i].length -= 1;
				}
			}
		}
		alias IDX = staticIndexOf!(C, U_TYPES);
		_data[IDX].remove(entity);
	}
}





//==============================================================================
/// 
mixin template EntityComponentSystemManager(SYSTEMS...) if(SYSTEMS.length > 0) {  

	private alias _ExtractQueries(SYSTEM) = Filter!(isQuery, __traits(getAttributes, SYSTEM));

	private template _GEN_QUERIES(SYSTEMS...) if(SYSTEMS.length > 0) {
		alias P = SYSTEMS[0];
		alias Q = _ExtractQueries!(SYSTEMS[0]);
		static if(SYSTEMS.length > 1) {
			alias NEXT = _GEN_QUERIES!(SYSTEMS[1..$]);
			alias _GEN_QUERIES = TypeTuple!(Q, NEXT);
		}
		else {
			alias _GEN_QUERIES = Q;
		}
	}

	alias QUERIES = _GEN_QUERIES!SYSTEMS;	 
	mixin EntityComponentManager!QUERIES;

	SYSTEMS _systems;

	pragma(msg, "\t", "Managed Systems:");
	pragma(msg, "\t", SYSTEMS);		   
	pragma(msg, "\t", "==================================");	
	pragma(msg, "");

public:
	///
	enum hasSystem(S) = staticIndexOf!(S, SYSTEMS) != -1;

public:	   
	///
	auto getSystem(S)() if(hasSystem!S) {	  
		alias IDX = staticIndexOf!(S, SYSTEMS);
		static assert(IDX != -1, "not a valid system");	
		return _systems[IDX];
	}

protected:	  
	///
	void startup() {
		foreach(ref s; this._systems) {	   
			writeln("# ", typeof(s).stringof, ".startup");

            static if(__traits(hasMember, typeof(s), "__ctor")) {
                s = new typeof(s)(this);
            }
            else {
                s = new typeof(s);
            }
		}
	}		   

	///
	void teardown() {
		foreach(ref s; this._systems) {
			if(s is null) continue;
			writeln("# ", typeof(s).stringof, ".teardown");	
			s.destroy();
			s = null;
		}
	}

	///
	void runSystems() {
		foreach(s; this._systems) {	  
			assert(s !is null);
			s.run(this);
		}
	}		   
}
