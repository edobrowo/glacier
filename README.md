# Glacier
Hierarchical, physically-based path tracing renderer.

# Building

```bash
cmake -H. -Bbuild

cmake --build build
```

# Running examples
```bash
./bin/Glacier examples/example

for file in examples/*.py; do ./bin/Glacier "$file"; done
```
