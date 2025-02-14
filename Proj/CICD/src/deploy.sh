#/bin/bash
PATHS=("src/cat/s21_cat" "src/grep/s21_grep")

for file in "${PATHS[@]}"
do
  scp $file anton@172.24.116.8:/usr/local/bin
  if [ $? -ne 0 ]; then
    echo "err"
    exit 1
  fi
done

