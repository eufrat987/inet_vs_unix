num="$1"
find . -type f -exec sed -ri "s/define BUFFER_SIZE [0-9]+/define BUFFER_SIZE $num/g"  {} \;
