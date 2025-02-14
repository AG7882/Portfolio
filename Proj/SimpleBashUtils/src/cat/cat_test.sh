#!/bin/bash



mkdir -p test_directory
cp ./s21_cat test_directory/
cp ../common/qwerty1.txt ../common/qwerty2.txt ../common/qwerty3.txt ../common/qwerty4.txt ../common/qwerty5.txt test_directory/
cp ../common/regs.txt test_directory/
cd test_directory/

v1="qwerty1.txt"
v2="qwerty2.txt"
v3="qwerty3.txt"
v4="qwerty4.txt"
v5="qwerty5.txt"

tcompl=0
tall=660

for vararg2 in "-e" "-E" "-v" "-t" "-T" "-n" "-b" "-s" "--number-nonblank" "--number" "--squeeze-blank"
do
for vararg in  "-e" "-E" "-v" "-t" "-T" "-n" "-b" "-s" "--number-nonblank" "--number" "--squeeze-blank"
do
for varn in "$v1" "$v2" "$v3" "$v4" "$v5"
do

str1=$(cat   "$vararg" "$vararg2" "$varn" )
str2=$(./s21_cat  "$vararg" "$vararg2" "$varn")
cat  "$vararg" "$vararg2" "$varn" > tmp1
./s21_cat  "$vararg" "$vararg2" "$varn" > tmp2
if [ "$str1" = "$str2" ]; then
echo "TEST COMPLETED"
tcompl=$(($tcompl+1))
else
diffs=$(diff tmp1 tmp2)
echo "TEST FAILED"
echo "./s21_grep 2 "$vararg" "$vararg2" "$varn""
echo "____________________________________________"
echo "$str1|"
echo "____________________________________________"
echo "$str2|"
echo "____________________________________________"
echo "$diffs"
echo "======================================================================"
fi
done
done
    done


for vararg in  "-e" "-E" "-v" "-t" "-T" "-n" "-b" "-s" "--number-nonblank" "--number" "--squeeze-blank" 

do


for varn in "$v1" "$v2" "$v3" "$v4" "$v5"
do
str1=$(cat "$vararg" "$varn")
str2=$(./s21_cat "$vararg" "$varn")
cat "$vararg" "$varn" > tmp1
./s21_cat "$vararg" "$varn" > tmp2
if [ "$str1" = "$str2" ]; then
echo "TEST COMPLETED"
tcompl=$(($tcompl+1))
else
diffs=$(diff tmp1 tmp2)
echo "TEST FAILED"
echo "cat $vararg $varn"
echo "______________________________________________________________________"
echo "$str1|"
echo "______________________________________________________________________"
echo "$str2|"
echo "______________________________________________________________________"
echo "$diffs"
echo "==================================================================================="
fi
done
done
    

str3=""
str4="-f"
str5="-e"
i=1
while [ "$i" -le 301 ];
do
str3="${str3}qwerty"
str4="${str4}qwerty"
i=$(($i+1))
done










echo "Completed:$tcompl/$tall"


cd ..
rm -rf ./test_directory