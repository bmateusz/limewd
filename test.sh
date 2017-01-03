#/bin/sh

SOURCES='src/*[ch]'
RET=0

grep '[[:blank:]]$' $SOURCES
if [ $? -ne 1 ]
then
  echo "Code contains trailing spaces"
  RET=1
fi

grep -P '\t' $SOURCES
if [ $? -ne 1 ]
then
  echo "Code contains tabs"
  RET=1
fi

exit $RET
