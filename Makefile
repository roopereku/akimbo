HEADER	=	$(wildcard *.hh)
SOURCE	=	$(wildcard *.cc)

OBJECT_DEBUG	=	$(addprefix obj/debug/,$(addsuffix .o,$(SOURCE)))
OBJECT_RELEASE	=	$(addprefix obj/release/,$(addsuffix .o,$(SOURCE)))

debug:	obj/ $(OBJECT_DEBUG)
	@make -C akimbo debug
	@g++ -o akimboengine $(OBJECT_DEBUG) akimbo/obj/debug/*.cc.o -lSDL2 -lSDL2_image -lSDL2_ttf

release:	obj/ $(OBJECT_RELEASE)
	@make -C akimbo release
	@g++ -o akimboengine $(OBJECT_RELEASE) akimbo/obj/release/*.cc.o -lSDL2 -lSDL2_image -lSDL2_ttf

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
