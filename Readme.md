# What

(2024-05, 2024-06, 2024-10)

Arduino library to get "entity" from Serial.

"Entity" is something surrounded by spaces.

## Example interaction

Example is getting entities which are no longer than `8` characters and
adds them to list.

When entity is `print`, list is printed.

Here we're pasting greeting text up to word `print`. List is printed.

It proves we can handle long inputs.

```
[me_SerialTokenizer] Okay, we are here.
We are capturing space-separated entries from serial input.
Maximum entry length: 00008
Type 'print' to print list.
Type 'clear' remove items from list.
Type 'exit' to leave.
me_SerialTokenizer] Okay, we are here.
We are capturing space-separated entries from serial input.
Maximum entry length: 00008
Type 'print' to print list.
--
  Okay,
  we
  are
  here.
  We
  are
  entries
  from
  serial
  input.
  Maximum
  entry
  length:
  00008
  Type
  'print'
  to
==
exit
[me_SerialTokenizer] Done.
```

## Requirements

  * arduino-cli
  * bash


## Install

Run [Install.sh](Install.sh).


## Remove

Run [Remove.sh](Remove.sh).


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Example]: examples/me_SerialTokenizer/me_SerialTokenizer.ino
[Interface]: src/me_SerialTokenizer.h
[Implementation]: src/me_SerialTokenizer.cpp

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
