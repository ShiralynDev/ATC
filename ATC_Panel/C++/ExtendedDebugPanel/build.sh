set -e

BUILD_DIR=build

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

if [ ! -f CMakeCache.txt ]; then
    echo "Configuring project..."
    cmake ..
else
    echo "Build system already configured. Skipping cmake..."
fi

cmake --build . --parallel