cd unix/server
meson setup build
cd build 
meson compile

cd ../../../unix/client
meson setup build
cd build 
meson compile

cd ../../../inet/server
meson setup build
cd build 
meson compile

cd ../../../inet/client
meson setup build
cd build 
meson compile
