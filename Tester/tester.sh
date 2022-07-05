echo "=-=-=-=-=-=-=-=-=-=-=-="
echo "=        TESTER       ="
echo "=-=-=-=-=-=-=-=-=-=-=-="
c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror -std=c++98 -D STATUS=1 tester.cpp -o tester.out && time ./tester.out > stdOut
c++ -g -O0 -fsanitize=address -Wall -Wextra -Werror -std=c++98 -D STATUS=0 tester.cpp -o tester.out && time ./tester.out > ftOut
#cat -e ftOut
echo "=-=-=-=-= DIFF =-=-=-=-="
diff stdOut ftOut
echo "=-=-=-= END DIFF =-=-=-="
rm -rf stdOut ftOut tester.out ./*.dSYM
