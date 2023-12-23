g++  -std=c++17 ./src/*.cpp -I./include -o ./bin/app -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
install_name_tool -add_rpath /Library/Frameworks/ ./bin/prog