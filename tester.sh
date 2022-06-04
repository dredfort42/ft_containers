c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror -std=c++98 -D STATUS=1 ./vector/*.cpp -o vector.out && time ./vector.out > stdVector
c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror -std=c++98 -D STATUS=0 ./vector/*.cpp -o vector.out && time ./vector.out > ftVector
echo "=-=-=-=-= DIFF =-=-=-=-="
diff stdVector ftVector
echo "=-=-=-= END DIFF =-=-=-="
cat -e ftVector
rm -rf stdVector ftVector vector.out ./*.dSYM
