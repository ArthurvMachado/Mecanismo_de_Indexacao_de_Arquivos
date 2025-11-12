all:
	g++ CommandLineInterface.cpp Index.cpp Indexer.cpp QueryProcessor.cpp Serializer.cpp TextProcessor.cpp -o ferreirinha.exe

clean:
ifeq ($(OS),Windows_NT)
	del ferreirinha.exe 
else
	rm -f ferreirinha.exe
endif