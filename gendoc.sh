#!/bin/sh
set -e

GH_REPO="github.com/bmateusz/limewd"

rm -rf docs
mkdir -p docs/html
git clone -b gh-pages "http://$GH_REPO" docs/html
make doc
cd docs/html

if [ -f "index.html" ]
then

  echo 'Uploading documentation to the gh-pages branch'
  git config user.name "Travis CI"
  git config user.email "travis@travis-ci.org"
  git add --all
  git commit -m "Travis build: ${TRAVIS_BUILD_NUMBER}, Commit: ${TRAVIS_COMMIT}"
  git push --force "https://${GH_TOKEN}@${GH_REPO}" gh-pages > /dev/null 2>&1

else
  echo 'No documentation found'
  exit 1
fi
