#/bin/sh

SOURCES='src/*[ch]'
RET=0

check()
{
  if [ $? -ne 1 ]
  then
    echo $1
    RET=$((RET+1))
  fi
}

check_empty()
{
  if [ $# -ne 1 ]
  then
    echo $*
    RET=$((RET+1))
  fi
}

grep '[[:blank:]]$' $SOURCES
check "Code contains trailing spaces"

grep -P '\t' $SOURCES
check "Code contains tabs"

check_empty "Working direcroty contains swap files:" $(find . -name *.sw*)

exit $RET
