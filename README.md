# Pintos

### setup environment
```
bash
SWD=/Users/sadegh/Desktop/pintos/src/misc/toolchain
PREFIX=$SWD/x86_64
export PATH=$PREFIX/bin:$PATH
export DYLD_LIBRARY_PATH=$PREFIX/lib:$DYLD_LIBRARY_PATH
fish
```

### build
```
cd src/threads
make
cd ../userprog
make
cd ../examples
make
cd ../userprog/build
```

### run example
```
# create filesys
pintos-mkdisk filesys.dsk --filesys-size=2

# format filesys
pintos -- -q -f

# copy example to filesys
pintos -p ../../examples/io -a io -- -q

# run example
pintos -- run io
```


