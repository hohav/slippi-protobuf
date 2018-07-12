# slippi-protobuf

This is a demo of encoding and decoding slippi events with [protobuf-c](https://github.com/protobuf-c/protobuf-c). `slippi.pb-c.c` and `slippi.pb-c.h` were generated from `slippi.proto` via `protoc-c`. If you modify slippi.proto, run `protoc-c slippi.proto --c_out=.` to regenerate slippi.pb-c.*.

`encode.c` and `decode.c` are just test programs that demonstrate the protobuf-c API. To build them, run `gcc slippi.pb-c.c encode.c -lprotobuf-c encode` and `gcc slippi.pb-c.c decode.c -lprotobuf-c decode`. You'll need protobuf-c even if you didn't modify slippi.proto, since the generated code relies on the protobuf-c library.
