all:
ifeq ($(OS),Windows_NT)
	g++ commandLineInterface/commandLineInterface.cpp index/index.cpp indexer/indexer.cpp queryProcessor/queryProcessor.cpp serializer/serializer.cpp textProcessor/textProcessor.cpp -o ferreirinha.exe 
else
	g++ commandLineInterface/commandLineInterface.cpp index/index.cpp indexer/indexer.cpp queryProcessor/queryProcessor.cpp serializer/serializer.cpp textProcessor/textProcessor.cpp -o ferreirinha
endif
	
clean:
ifeq ($(OS),Windows_NT)
	del ferreirinha.exe 
else
	rm -f ferreirinha.exe
endif