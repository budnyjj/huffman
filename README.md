huffman
=======

Simple implementation of [huffman coding algorithm](https://www.cs.auckland.ac.nz/~jmor159/PLDS210/huffman.html).

compilation
-----------

```bash
make; 
```

tests
-----
```
make test
```

usage
-----

```bash
# compress data.txt to data.hf
./bin/hf -c data.hf data.txt

# decompress data.hf to data.txt
./bin/hf -x data.txt data.hf
```
