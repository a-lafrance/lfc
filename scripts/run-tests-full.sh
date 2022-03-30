# !/bin/bash

make tests
BUILD_RESULT=$?

if [ $BUILD_RESULT != 0 ]
then
	echo "failed to build library with exit code: $BUILD_RESULT"
	exit $BUILD_RESULT
fi

valgrind --error-exitcode=1 --leak-check=full -q ./target/tests
TEST_RESULT=$?

if [ $TEST_RESULT != 0 ]
then
	OUTCOME="failed"
else
	OUTCOME="succeeded"
fi

echo "tests $OUTCOME with exit code: $TEST_RESULT"
exit $TEST_RESULT
