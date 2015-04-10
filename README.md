huffman
=======

Simple implementation of [huffman coding algorithm](https://www.cs.auckland.ac.nz/~jmor159/PLDS210/huffman.html).

building
--------

```bash
./configure
make
```

run tests
---------
```
./configure
make test
```

usage
-----

```bash
# compress data.txt to data.hf
./src/huffman -c data.hf data.txt

# decompress data.hf to data.txt
./bin/huffman -x data.txt data.hf
```
