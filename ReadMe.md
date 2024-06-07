# What

(2024-05, 2024-06)

Arduino library to get "entity" from Serial.

"Entity" is something surrounded by spaces.

## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## Details

Warningless compilation (-std=c++1z):

```bash
arduino-cli compile . --fqbn arduino:avr:uno --quiet --warnings all --build-property compiler.cpp.extra_flags="-std=c++1z"
```

Sample output:

```
[me_SerialTokenizer] Okay, we are here.
We are capturing space-separated entries from serial input.
Maximum entry length: 8

Type 'exit' to leave.
ds df s da 43l4k3lkerlkds;hjf  3kjdfskjsk exit dkjlsfkld
[1] 2 (ds)
[2] 2 (df)
[3] 1 (s)
[4] 2 (da)
[5] 8 (43l4k3lk)..
[6] 8 (3kjdfskj)..
[7] 4 (exit)
Done.
```

[Example](examples/me_SerialTokenizer/me_SerialTokenizer.ino)

[Code](src/me_SerialTokenizer.cpp)


## See also

[My other repositories](https://github.com/martin-eden/contents).
