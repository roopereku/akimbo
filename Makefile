HEADER	=	$(wildcard *.hh)
SOURCE	=	$(wildcard *.cc)

OBJECT_DEBUG	=	$(addprefix obj/debug/,$(addsuffix .o,$(SOURCE)))
OBJECT_RELEASE	=	$(addprefix obj/release/,$(addsuffix .o,$(SOURCE)))

debug:	obj/ $(OBJECT_DEBUG)
	@make -C akimbo debug
	@g++ -o akimboengine $(OBJECT_DEBUG) akimbo/obj/debug/*.cc.o akimbo/obj/debug/ui/*.cc.o -lSDL2 -lGL -lGLEW

release:	obj/ $(OBJECT_RELEASE)
	@make -C akimbo release
	@g++ -o akimboengine $(OBJECT_RELEASE) akimbo/obj/release/*.cc.o akimbo/obj/release/ui/*.cc.o -lSDL2 -lGL -lGLEW

obj/debug/%.cc.o:	%.cc $(HEADER)
	@echo "Building $< in debug mode"
	@g++ -c -o $@ $< -std=c++17 -pedantic -Wall -Wextra -g -D DEBUG

obj/release/%.cc.o:	%.cc $(HEADER)
	@echo "Building $< in release mode"
	@g++ -c -o $@ $< -std=c++17 -pedantic -Wall -Wextra -O3

obj/:
	@mkdir -p obj/debug
	@mkdir -p obj/release

clean:
	@rm -rf obj/
	@rm -f akimboengine
	@make -C akimbo clean
