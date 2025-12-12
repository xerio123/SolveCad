// Copyright 2021 The Manifold Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "manifold/cross_section.h"
#include "manifold.h"

namespace {

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
}  // namespace

namespace manifold {

/**
 * Creates a classic torus knot, defined as a string wrapping periodically
 * around the surface of an imaginary donut. If p and q have a common factor
 * then you will get multiple separate, interwoven knots. This is an example of
 * using the Manifold.Warp() method, thus avoiding any handling of triangles.
 *
 * @param p The number of times the thread passes through the donut hole.
 * @param q The number of times the thread circles the donut.
 * @param majorRadius Radius of the interior of the imaginary donut.
 * @param minorRadius Radius of the small cross-section of the imaginary donut.
 * @param threadRadius Radius of the small cross-section of the actual object.
 * @param circularSegments Number of linear segments making up the threadRadius
 * circle. Default is Quality.GetCircularSegments().
 * @param linearSegments Number of segments along the length of the knot.
 * Default makes roughly square facets.
 */
Manifold TorusKnot(int p, int q, double majorRadius, double minorRadius,
                   double threadRadius, int circularSegments,
                   int linearSegments) {
  int kLoops = gcd(p, q);
  p /= kLoops;
  q /= kLoops;
  int n = circularSegments > 2 ? circularSegments
                               : Quality::GetCircularSegments(threadRadius);
  int m =
      linearSegments > 2 ? linearSegments : n * q * majorRadius / threadRadius;


  Manifold knot = Manifold::Cube({(1.0), (1.0), (1.0)},true);



  return knot;
}
}  // namespace manifold