
compile:
	g++ GSM.cpp -o run -L/usr/local/lib -ldb_cxx
clean:
	rm -rf ./run ./db/*
