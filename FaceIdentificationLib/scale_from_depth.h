/*
 * License: 3-clause BSD. See LICENSE file in root directory.
 * Copyright(c) 2015-2016 Intel Corporation. All Rights Reserved.
 * */

#include <iostream>
// using namespace std;
#ifndef SCALE_FROM_DEPTH_H
#define  SCALE_FROM_DEPTH_H
class Scale_Depth {
public:
  double m_dFcousPara;
public:
  Scale_Depth();
  ~Scale_Depth() = default;
  bool get_scale_from_depth(int Depth,int& Minscale,int &Maxscale);
  void Coordinate_Image_2_World(int nWidth, int nHeight, double ImageCoord[3], double WorldCoord[3]);
};
#endif
