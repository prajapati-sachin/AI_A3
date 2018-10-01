./compile.sh
./run1.sh $1
./minisat_static $1.satinput $1.satoutput
./run2.sh $1
cp $1.graph ./a3_format_checker_scripts
cp $1.subgraphs ./a3_format_checker_scripts
cd a3_format_checker_scripts
python checker.py $1.graph $1.subgraphs
rm $1.graph
rm $1.subgraphs
cd ..
rm $1.subgraphs
rm $1.satinput
rm $1.satoutput