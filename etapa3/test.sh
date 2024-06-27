#! /bin/sh
# rebuild prog if necessary
make etapa3
# run prog with some arguments
./etapa3 "$@" out.txt 
./etapa3 out.txt out2.txt
output=`diff ./out.txt ./out2.txt`
if [ -z "$output" ];
then
    echo "etapa3 test success"
else
    echo "etapa3 test FAILED"
fi