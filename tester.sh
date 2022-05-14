c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror  -D STATUS=1 ./vector/*.cpp -o vector.out && ./vector.out > stdVector
c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror  -D STATUS=0 ./vector/*.cpp -o vector.out && ./vector.out > ftVector
echo "=-=-=-=-= DIFF =-=-=-=-="
diff stdVector ftVector
echo "=-=-=-= END DIFF =-=-=-="
cat -e ftVector
rm stdVector ftVector vector.out
