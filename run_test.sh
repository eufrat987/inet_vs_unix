echo Inet test
cd inet/server/build
./server &
sleep 2
cd ../../client/build
time ./client

cd ../../..
echo ''

echo Unix test
cd unix/server/build
./server &
sleep 2
cd ../../client/build
time ./client
