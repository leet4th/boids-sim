# boids-sim

## Build

```bash
cmake -S . -B build
cmake --build build -j
./build/apps/boids-sim
```

## clang-format

```bash
find . -path ./build -prune -o \( -name "*.hpp" -o -name "*.cpp" \) -print | xargs clang-format -i
```