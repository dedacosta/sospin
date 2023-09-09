all : install
	@#
	
.PHONY : clean install deploy doc

clean :
	@find . -name ".DS_Store" | xargs rm -rf
	@find . -name ".project" | xargs rm -rf
	@find . -name "build" | xargs rm -rf
	@rm -rf .settings out
	
install: 
	@cmake -S . -B build
	@cmake --build build 
	@cmake --install build
	   
deploy :
	@cp out/lib/libsospin.a ${HOME}/dev/local/lib
	@cp -r out/include/* ${HOME}/dev/local/include

doxygen-doc :
	@make -f build/doc/Makefile doxygen-doc

doc : doxygen-doc
	@#
