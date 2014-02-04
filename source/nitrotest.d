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

module nitrotest;

//###################################################################################################

import nitro;

//###################################################################################################

final class SystemOne(ECM) {
	string _identifier;

	this() {
		_identifier = "SystemOne";
		import std.stdio;
		writeln(_identifier, " this()");
	}

	void run(ECM ecm) {
		import std.stdio;
		writeln(_identifier, " RUN");

		foreach(e; ecm.query!ComponentThree()) {
			writeln("ComponentThree found");
			ecm.deleteLater!ComponentThree(e);
			ecm.deleteLater(e);

			ecm.addComponents(ecm.createEntity(), ComponentOne(10,"a",true), ComponentThree());
			ecm.addComponents(ecm.createEntity(), ComponentTwo(11,"b",false), ComponentThree());
		}
		ecm.deleteNow();
	}
}

final class SystemTwo(ECM) {
	ECM _ecm;
	string _identifier;

	this(ECM ecm) {
		_identifier = "SystemTwo";
		_ecm = ecm;
		import std.stdio;
		writeln(_identifier, " this(ECM ecm)");
	}

	void run(ECM ecm) {
		import std.stdio;
		writeln(_identifier, " RUN");

		foreach(e; ecm.query!ComponentThree()) {
			Entity en = e;
			if(e.hasComponent!ComponentOne()) {
				auto component = e.getComponent!ComponentOne();
				writeln("Entity ", en , ", component one: ", component.FieldOne, ", ", component.FieldTwo, ", ", component.FieldThree);
			}
			if(e.hasComponent!ComponentTwo()) {
				auto component = e.getComponent!ComponentTwo();
				writeln("Entity ", en , ", component two: ", component.FieldOne, ", ", component.FieldTwo, ", ", component.FieldThree);
			}
			ecm.clearLater(e);
		}

		ecm.deleteNow();
	}
}

//---------------------------------------------------------------------------------------------------

struct ComponentOne {
	int FieldOne;
	string FieldTwo;
	bool FieldThree;
}

struct ComponentTwo { 
	int FieldOne;
	string FieldTwo;
	bool FieldThree;
}

struct ComponentThree {

}

//---------------------------------------------------------------------------------------------------

@System final class SystemThree(ECM) {

}

@System final class SystemFour(ECM) {

}

@Component struct ComponentFour {

}

@Component struct ComponentFive {

}

//---------------------------------------------------------------------------------------------------

void NitroTest() {
	import std.stdio;
	import std.typetuple;

	writeln("");
	writeln("################# NITRO TEST START #################");
	writeln("");

	alias TEST_SYSTEMS = TypeTuple!(SystemOne, SystemTwo);
	alias TEST_COMPONENTS = TypeTuple!(ComponentOne, ComponentTwo, ComponentThree);

	alias TEST_ECM = EntityComponentManager!(TEST_COMPONENTS);
	alias TEST_ECS = SystemManager!(TEST_ECM, TEST_SYSTEMS);

	// Test system functions
	TEST_ECS test_ecs = new TEST_ECS();

	auto system_one = test_ecs.system!SystemOne();
	auto system_two = test_ecs.system!SystemTwo();

	writeln("SystemOne identifier: ", system_one._identifier);
	writeln("SystemTwo identifier: ", system_two._identifier);

	test_ecs.run();


	// Test entity/component functions
	auto test_ecm = test_ecs.ecm;

	Entity entity_one = test_ecm.createEntity();
	Entity entity_two = test_ecm.createEntity();
	Entity entity_three = test_ecm.createEntity();

	if(!test_ecm.isValid(entity_one)) writeln("Entity one should be valid");
	if(!test_ecm.isValid(entity_two)) writeln("Entity two should be valid");
	if(!test_ecm.isValid(entity_three)) writeln("Entity three should be valid");

	test_ecm.deleteLater(entity_three);
	test_ecm.deleteNow();

	if(!test_ecm.isValid(entity_one)) writeln("Entity one should be valid");
	if(!test_ecm.isValid(entity_two)) writeln("Entity two should be valid");
	if(test_ecm.isValid(entity_three)) writeln("Entity three should NOT be valid");

	if(test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity one should not have components");
	if(test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity two should not have components");

	test_ecm.addComponents(entity_one, ComponentOne(1, "hi", true));
	if(!test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should not have component ComponentTwo");

	if(test_ecm.hasComponents!(ComponentOne,ComponentTwo)(entity_one)) writeln("Entity should not have component ComponentOne and ComponentTwo");

	test_ecm.deleteLater!ComponentOne(entity_one);
	test_ecm.deleteNow();

	if(test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should not have component ComponentTwo");

	test_ecm.addComponents(entity_two, ComponentOne(2, "ho", false));
	test_ecm.addComponents(entity_two, ComponentTwo(3, "lets", true));

	if(test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should not have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should have component ComponentTwo");

	test_ecm.addComponents(entity_one, ComponentOne(4, "go", false));
	test_ecm.addComponents(entity_one, ComponentTwo(5, "this", true));

	if(!test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should have component ComponentTwo");

	if(!test_ecm.hasComponents!(ComponentOne,ComponentTwo)(entity_one)) writeln("Entity should have component ComponentOne and ComponentTwo");
	if(!test_ecm.hasComponents!(ComponentOne,ComponentTwo)(entity_two)) writeln("Entity should have component ComponentOne and ComponentTwo");

	auto component_one = test_ecm.getComponent!ComponentOne(entity_one);
	writeln("Entity one, component one: ", component_one.FieldOne, ", ", component_one.FieldTwo, ", ", component_one.FieldThree);

	Entity lastEntity = Entity(9999);
	foreach(e; test_ecm.query!(ComponentOne, ComponentTwo)()) {
		if(!e.hasComponent!ComponentOne()) writeln("Entity should have component");
		if(!e.hasComponent!ComponentTwo()) writeln("Entity should have component");

		auto component = e.getComponent!ComponentOne();
		Entity en = e;
		writeln("Entity ", en ,", component one: ", component.FieldOne, ", ", component.FieldTwo, ", ", component.FieldThree);

		auto componenttwo = e.getComponent!ComponentTwo();
		Entity entwo = e;
		writeln("Entity ", entwo ,", component two: ", componenttwo.FieldOne, ", ", componenttwo.FieldTwo, ", ", componenttwo.FieldThree);

		if(en != entwo) writeln("Something is very wrong");
		if(lastEntity != Entity(9999)) {
			if(en > lastEntity) writeln("Entities should be queried in creation order!");
		}
		lastEntity = en;
	}

	test_ecm.deleteLater!ComponentTwo(entity_one);
	test_ecm.deleteLater!ComponentOne(entity_two);
	test_ecm.deleteNow();

	foreach(e; test_ecm.query!ComponentOne()) {
		if(!e.hasComponent!ComponentOne()) writeln("Entity should have component");
		if(e.hasComponent!ComponentTwo()) writeln("Entity should not have component");

		auto component = e.getComponent!ComponentOne();
		Entity en = e;
		writeln("Entity ", en ,", component one: ", component.FieldOne, ", ", component.FieldTwo, ", ", component.FieldThree);
	}

	foreach(e; test_ecm.query!ComponentTwo()) {
		if(e.hasComponent!ComponentOne()) writeln("Entity should not have component");
		if(!e.hasComponent!ComponentTwo()) writeln("Entity should have component");

		auto component = e.getComponent!ComponentTwo();
		Entity en = e;
		writeln("Entity ", en ,", component two: ", component.FieldOne, ", ", component.FieldTwo, ", ", component.FieldThree);
	}


	if(!test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should not have component ComponentOne");
	if(!test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should have component ComponentTwo");

	if(!test_ecm.isValid(entity_one)) writeln("Entity one should be valid");
	if(!test_ecm.isValid(entity_two)) writeln("Entity two should be valid");

	test_ecm.deleteLater!ComponentOne(entity_one);
	test_ecm.deleteLater!ComponentTwo(entity_two);
	test_ecm.deleteNow();

	if(test_ecm.hasComponents!ComponentOne(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_one)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentOne(entity_two)) writeln("Entity should not have component ComponentOne");
	if(test_ecm.hasComponents!ComponentTwo(entity_two)) writeln("Entity should not have component ComponentTwo");

	test_ecm.deleteLater(entity_one);
	test_ecm.deleteLater(entity_two);
	test_ecm.deleteNow();

	if(test_ecm.isValid(entity_one)) writeln("Entity one should NOT be valid");
	if(test_ecm.isValid(entity_two)) writeln("Entity two should NOT be valid");

	Entity entity_emitter = test_ecm.createEntity();
	test_ecm.addComponents(entity_emitter, ComponentThree());

	test_ecs.run();
	test_ecs.run();

	// Test gen ecs functionality
	mixin MakeECS!("nitrotest");
	ecs.run();
	ecs.run();

	// TODO: Test MakeECS generated systems
	// TODO: Test autoquery

	writeln("");
	writeln("################# NITRO TEST STOP  #################");
	writeln("");
	return;
}
