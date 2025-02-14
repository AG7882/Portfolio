#!/bin/bash



mkdir -p test_directory
cp ./s21_grep test_directory/
cp ./grep_test2.sh test_directory/
cp ../common/qwerty1.txt ../common/qwerty2.txt ../common/qwerty3.txt ../common/qwerty4.txt ../common/qwerty5.txt  ../common/qwertyseg.txt test_directory/
cp ../common/regs.txt test_directory/
cd test_directory/








v1="qwerty5.txt"
v2="qwerty5.txt"
v3="qwerty5.txt"
v4="qwerty4.txt"
v5="qwerty5.txt"
reg="regs.txt"
tcompl=0
tall=0


for vararg in  "-e a" "-e aS" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "aS" "2" "6sa5d4f6sd11a6sf4daf1" "-f6sa5d4f6sd11a6sf4daf1" "-f" "regs.txt" "qwerty5.txt"
do
for varn in "$v1" "$v2" "$v3" "$v4" "$v5"
do
tall=$(($tall+1))
str1=$(grep 2 $vararg  $varn )
str2=$(./s21_grep 2 $vararg  $varn)
grep 2 "$vararg"  "$varn" > tmp1
./s21_grep 2 "$vararg" "$varn" > tmp2
if [ "$str1" = "$str2" ]; then
echo "TEST COMPLETED"
tcompl=$(($tcompl+1))
else
diffs=$(diff -s tmp1 tmp2)
echo "TEST FAILED"
echo "./s21_grep 2 $vararg $vararg2 $varn"
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


for vararg2 in "-e" "-e a" "-e aS" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "6sa5d4f6sd11a6sf4daf1" "-f6sa5d4f6sd11a6sf4daf1" "-f" "regs.txt" "qwerty5.txt"
do
for vararg in  "-e a" "-e aS" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "aS" "2" "6sa5d4f6sd11a6sf4daf1" "-f6sa5d4f6sd11a6sf4daf1" "-f" "regs.txt" "qwerty5.txt"
do
for varn in "$v1" "$v2" "$v3" "$v4" "$v5"
do
tall=$(($tall+1))
str1=$(grep 2 $vararg $vararg2 $varn )
str2=$(./s21_grep 2 $vararg $vararg2 $varn)
grep 2 "$vararg" "$vararg2" "$varn" > tmp1
./s21_grep 2 "$vararg" "$vararg2" "$varn" > tmp2
if [ "$str1" = "$str2" ]; then
echo "TEST COMPLETED"
tcompl=$(($tcompl+1))
else
diffs=$(diff -s tmp1 tmp2)
echo "TEST FAILED"
echo "./s21_grep 2 $vararg $vararg2 $varn"
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


for vararg in  "-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "-fqwerty5.txt"
do
tall=$(($tall+1))

str1=$(grep "$vararg" 2 qwerty5.txt )
str2=$(./s21_grep "$vararg" 2 qwerty5.txt)
grep "$vararg" 2 qwerty5.txt > tmp1
./s21_grep "$vararg" 2 qwerty5.txt > tmp2
if [ "$str1" = "$str2" ]; then
echo "TEST COMPLETED"
tcompl=$(($tcompl+1))
else
diffs=$(diff tmp1 tmp2)
echo "TEST FAILED: $tall"
echo "./s21_grep "$vararg" 2 qwerty5.txt"
echo "____________________________________________"
echo "$str1|"
echo "____________________________________________"
echo "$str2|"
echo "____________________________________________"
echo "$diffs"
echo "======================================================================"
fi
done





echo "Completed:$tcompl/$tall   Next look for seg faults"



#echo "./s21_grep 2  "-f" "300s" "qwertyseg.txt""
./s21_grep 2  "$str4" "$str3" "qwertyseg.txt"
#echo "./s21_grep 2  "-e" "300s" "qwertyseg.txt""
./s21_grep 2  "$str5" "$str3" "qwertyseg.txt"
#echo "./s21_grep 2  "300s" "300s" "qwertyseg.txt""
./s21_grep 2  "$str3" "$str3" "qwertyseg.txt"
#echo "./s21_grep 2  "-f300s" "qwertyseg.txt""
./s21_grep 2  "$str4$str3" "qwertyseg.txt"
./s21_grep   "$str4$str3"
./s21_grep   "$str4$str3"  "$str4$str3"



cd ..
rm -rf ./test_directory