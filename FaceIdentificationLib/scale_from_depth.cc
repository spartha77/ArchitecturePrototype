/*
 * License: 3-clause BSD. See LICENSE file in root directory.
 * Copyright(c) 2015-2016 Intel Corporation. All Rights Reserved.
 * */

#include "scale_from_depth.h"

Scale_Depth::Scale_Depth() {
  m_dFcousPara = 620.0;
}

bool Scale_Depth::get_scale_from_depth(int Depth,int &Minscale,int& Maxscale) {
  if (!Depth) {
    return false;
  }
  int MinHead = 150;
  int MaxHead = 250;
  Minscale = (double)MinHead * m_dFcousPara/Depth;
  Maxscale = (double)MaxHead * m_dFcousPara/Depth;
//  Minscale = (double)MinHead * (double)Depth /1200.0;
//  Maxscale = (double)MaxHead * (double)Depth /1200.0;
  return true;
}


////////////////////////////////////////////////////////////////////////////////////////
/// This routine is a function of CFaceAttributeRecognition
///  written by Ren Haibing
/// Acknowledge    :
///
/// Function name  : Coordinate_Image_2_World
/// Description      : change the coordinate from image(x,y,depth) to world(X,Y,Z)
///
/// Argument    : (nWidth, nHeight) -- image size
/// Argument    : ImageCoord -- (x,y,depth)
/// Argument    : WorldCoord -- (X,Y,Z)
///
/// Return type    :
///
/// Create Time    : 2015-3-5  16:09
///
///
/// Side Effect    :
///
///////////////////////////////////////////////////////////////////////////////////////////////
void Scale_Depth::Coordinate_Image_2_World(int nWidth, int nHeight,
                       double ImageCoord[3], double WorldCoord[3]) {
  double x = ImageCoord[0] - nWidth * 0.5;
  double y = nHeight * 0.5 - ImageCoord[1];

  WorldCoord[0] = x * ImageCoord[2]/m_dFcousPara;
  WorldCoord[1] = y * ImageCoord[2]/m_dFcousPara;
  WorldCoord[2] = ImageCoord[2];
}
