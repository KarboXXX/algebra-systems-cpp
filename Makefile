run: algebra.cpp
	g++ algebra.cpp -o al `pkg-config --cflags --libs gtk+-3.0`
	# x86_64-w64-mingw32-g++ algebra.cpp -o algebra.exe `pkg-config --cflags --libs gtk+-3.0`