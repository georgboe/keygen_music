# Keygen music

A project for the Raspberry Pi Pico 2 that will play [`.xm`](https://en.wikipedia.org/wiki/XM_(file_format)) files and output it via [I²S](https://en.wikipedia.org/wiki/I%C2%B2S).

## Getting Started

### Prerequisites

[Pico SDK](https://github.com/raspberrypi/pico-sdk) must be installed and the environment variable `PICO_SDK_PATH` must be set to its location.

### Building

```
$ mkdir build
$ cd build
$ cmake -DPICO_PLATFORM=rp2350 -DPICO_BOARD=pico2 ..
$ make
```

### Adding new chiptunes

```
$ xxd -i <tune>.xm > <tune>.h
```

Add `__in_flash()` to the variable declaration so it will reside in flash.

```diff
- unsigned char crack_xm[]
+ unsigned char __in_flash("crack") crack_xm[]
```

Then import the header file in `keygen_music.cpp` and load it.
```cpp
#include "tunes/<tune>.h"

...

m4p_LoadFromData((uint8_t*)tune_xm, tune_xm_len, rate, buffer_size);
```

## Licenses

### Chip tunes

All the included chiptunes are copright of their composers and licensed under under the [Mod Archive Distribution license](https://modarchive.org/index.php?terms-upload)

`crack.h`: https://modarchive.org/index.php?request=view_by_moduleid&query=39429   
`ghidapop.h`: https://modarchive.org/index.php?request=view_by_moduleid&query=43516   
`unreal.h`: https://modarchive.org/index.php?request=view_by_moduleid&query=149252

### mod4play

https://github.com/dashodanger/mod4play/

> BSD 3-Clause License   
> Copyright (c) 2023-2024, dashodanger   
> Copyright (c) 2020-2021, Olav Sørensen   
> 
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are > met:
> 
> 1. Redistributions of source code must retain the above copyright > notice, this
>    list of conditions and the following disclaimer.
> 
> 2. Redistributions in binary form must reproduce the above copyright > notice,
>    this list of conditions and the following disclaimer in the > documentation
>    and/or other materials provided with the distribution.
> 
> 3. Neither the name of the copyright holder nor the names of its
>    contributors may be used to endorse or promote products derived from
>    this software without specific prior written permission.
> 
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS > IS"
> AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
> IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR > PURPOSE ARE
> DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE > LIABLE
> FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR > CONSEQUENTIAL
> DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS > OR
> SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) > HOWEVER
> CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT > LIABILITY,
> OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF > THE USE
> OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
