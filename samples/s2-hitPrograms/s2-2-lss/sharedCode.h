// MIT License

// Copyright (c) 2022 Nathan V. Morrical

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "gprt.h"

/* variables available to all programs */

/* variables for the line-swept sphere geometry */
struct LSSGeomData {
  float4 *vertices;
  uint2 *indices;
};

struct RayGenData {
  uint *frameBuffer;
  gprt::Accel world;
};

/* variables for the miss program */
struct MissProgData {
  float3 color0;
  float3 color1;
};

/* Constants that change each frame */
struct PushConstants {
  float time;
};

#if defined(__SLANG_COMPILER__) // <- causes code below to only be included in the device code.
float3 pattern(in float2 uv) {
  float3 col = float3(0.6);
  col += 0.4 * smoothstep(-0.01, 0.01, cos(uv.x * 0.5) * cos(uv.y * 0.5));
  col *= smoothstep(-1.0, -0.98, cos(uv.x)) * smoothstep(-1.0, -0.98, cos(uv.y));
  return col;
}
#endif
