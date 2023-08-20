all : install
	@c#
	
.PHONY : clean install

clean :
	@find . -name ".DS_Store" | xargs rm -f
	@rm -rf build
	
install: 
	@cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	@cmake --build build 
	#@cmake --install build
	   
