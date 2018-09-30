./compile.sh
./run1.sh $1
./minisat_static $1.satinput $1.satoutput
./run2.sh
