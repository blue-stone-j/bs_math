
# colorful output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# rm -rf build &&
# rm -rf install &&

echo -e "${BLUE}Start working.${NC}"

# set variable
echo -e "${BLUE}Start setting variables.${NC}"
PROJECT_NAME=bmath
PROJECT_NAME_U=$(echo "$PROJECT_NAME" | tr '[:lower:]' '[:upper:]')
PROJECT_NAME_L=$(echo "$PROJECT_NAME" | tr '[:upper:]' '[:lower:]')

BMATH_VERSION_MAJOR=1
BMATH_VERSION_MINOR=0
BMATH_VERSION_PATCH=0
BMATH_VERSION=${BMATH_VERSION_MAJOR}.${BMATH_VERSION_MINOR}.${BMATH_VERSION_PATCH}

BUILD_TEST=TRUE

CMAKE_INSTALL_PREFIX=$(realpath $(dirname "${BASH_SOURCE[0]}"))/install
echo -e "${GREEN}Set variables completed.${NC}"

# build
echo -e "${BLUE}Start building.${NC}"
mkdir -p build &&
cd build &&
cmake -DBMATH_VERSION=${BMATH_VERSION} \
      -DCMAKE_INSTALL_PREFIX=$CMAKE_INSTALL_PREFIX \
      -DBUILD_TEST=$BUILD_TEST \
      ..

if [ ! $? -eq 0 ]; then
  echo -e "${RED}Failed to build.${NC}"
  exit
fi

cmake --build . --target install -j6 --config Release

if [ ! $? -eq 0 ]; then
  echo -e "${RED}Failed to build.${NC}"
  exit
fi

echo -e "${GREEN}Build completed.${NC}"

echo -e "${GREEN}All tasks have been done.${NC}"

