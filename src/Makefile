all:
	g++ commandLineInterface/commandLineInterface.cpp index/index.cpp indexer/indexer.cpp queryProcessor/queryProcessor.cpp serializer/serializer.cpp textProcessor/textProcessor.cpp -o ferreirinha.exe

clean:
ifeq ($(OS),Windows_NT)
	del ferreirinha.exe 
else
	rm -f ferreirinha.exe
endif