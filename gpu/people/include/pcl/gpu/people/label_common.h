/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2012, Willow Garage, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: $
 * @author: Koen Buys
 */

#ifndef PCL_GPU_PEOPLE_LABEL_COMMON_H_
#define PCL_GPU_PEOPLE_LABEL_COMMON_H_

// Some defines for the tree
#define ROOT        -1
#define LEAF        -2
#define NO_CHILD    -3
#define NUM_PARTS   25      // We have 25 body parts defined
#define MAX_CHILD   4       // a parent node has maximum 4 children

// Some defines for geometry
#define FOCAL     525       // Focal length of rgb camera in pixels
#define WIDTH     640
#define HEIGHT    480
#define RATIO     WIDTH/HEIGHT

#define MAX_NR_TREES  4

// Some defines for part image
#define NO_DATA   255       // We have no depth data for this part of the image

// Other defines
#define DEBUG     1

#define XML_VERSION 1

enum part_t 
{ 
  Lfoot = 0,
  Lleg = 1,
  Lknee = 2,
  Lthigh = 3,
  Rfoot = 4,
  Rleg = 5,
  Rknee = 6,
  Rthigh = 7,
  Rhips = 8,
  Lhips = 9,
  Neck = 10,
  Rarm = 11,
  Relbow = 12,
  Rforearm = 13,
  Rhand = 14,
  Larm = 15,
  Lelbow = 16,
  Lforearm = 17,
  Lhand = 18,
  FaceLB = 19,
  FaceRB = 20,
  FaceLT = 21,
  FaceRT = 22,
  Rchest = 23,
  Lchest = 24
};

/** @todo get this to work
std::string part_k[NUM_PARTS] = {"Lfoot","Lleg", "Lknee","Lthigh",
            "Rfoot","Rleg","Rknee","Rthigh",
            "Rhips","Lhips","Neck",
            "Rarm","Relbow","Rforearm","Rhand",
            "Larm","Lelbow","Lforearm","Lhand",
            "FaceLB","FaceRB","FaceLT","FaceRT",
            "Rchest","Lchest"};

inline std::ostream& operator << (std::ostream& os, const part_t& p)
{
  os << part_k[(int) p];
  return (os);
}
**/

namespace pcl
{
  namespace gpu
  {
    namespace people
    {
      namespace label_skeleton
      {

      /**
       * @brief This LUT contains the max primary eigenvalue for each part
       * @todo read this from XML file
       **/
      static const float LUT_max_part_size[] = 
      {
        0.5f,            // 0 Lfoot
        0.7f,            // 1 Lleg
        0.6f,            // 2 Lknee
        0.6f,            // 3 Lthigh
        0.5f,            // 4 Rfoot
        0.7f,            // 5 Rleg
        0.6f,            // 6 Rknee
        0.6f,            // 7 Rthigh
        0.9f,            // 8 Rhips
        0.9f,            // 9 Lhips
        0.5f,            // 10 Neck
        0.7f,            // 11 Rarm
        0.5f,            // 12 Relbow
        0.7f,            // 13 Rforearm
        0.5f,            // 14 Rhand
        0.7f,            // 15 Larm
        0.5f,            // 16 Lelbow
        0.7f,            // 17 Lforearm
        0.5f,            // 18 Lhand
        0.5f,            // 19 FaceLB
        0.5f,            // 20 FaceRB
        0.5f,            // 21 FaceLT
        0.5f,            // 22 FaceRT
        0.9f,            // 23 Rchest
        0.9f             // 24 Lchest
      };

      /**
       *  @brief This LUT contains the ideal lenght between this part and his children
       **/
      static const float LUT_ideal_length[][4] = {
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 0 Lfoot
        {  0.2f,  -1.0f,  -1.0f,  -1.0f}, // 1 Lleg
        {  0.2f,  -1.0f,  -1.0f,  -1.0f}, // 2 Lknee
        {  0.3f,  -1.0f,  -1.0f,  -1.0f}, // 3 Lthigh
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 4 Rfoot
        {  0.2f,  -1.0f,  -1.0f,  -1.0f}, // 5 Rleg
        {  0.2f,  -1.0f,  -1.0f,  -1.0f}, // 6 Rknee
        {  0.3f,  -1.0f,  -1.0f,  -1.0f}, // 7 Rthigh
        {  0.3f,  -1.0f,  -1.0f,  -1.0f}, // 8 Rhips
        {  0.3f,  -1.0f,  -1.0f,  -1.0f}, // 9 Lhips
        { 0.15f,  0.15f,   0.2f,   0.2f}, // 10 Neck
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 11 Rarm
        {  0.1f,  -1.0f,  -1.0f,  -1.0f}, // 12 Relbow
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 13 Rforearm
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 14 Rhand
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 15 Larm
        {  0.1f,  -1.0f,  -1.0f,  -1.0f}, // 16 Lelbow
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 17 Lforearm
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 18 Lhand
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 19 FaceLB
        { 0.15f,  -1.0f,  -1.0f,  -1.0f}, // 20 FaceRB
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 21 FaceLT
        { -1.0f,  -1.0f,  -1.0f,  -1.0f}, // 22 FaceRT
        {  0.3f,   0.3f,  -1.0f,  -1.0f}, // 23 Rchest
        {  0.3f,   0.3f,  -1.0f,  -1.0f}  // 24 Lchest
      };

      /**
       * @brief This LUT contains the max lenght between this part and his children
       **/
      static const float LUT_max_length_offset[][4] = {
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 0 Lfoot
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 1 Lleg
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 2 Lknee
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 3 Lthigh
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 4 Rfoot
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 5 Rleg
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 6 Rknee
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 7 Rthigh
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 8 Rhips
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 9 Lhips
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 10 Neck
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 11 Rarm
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 12 Relbow
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 13 Rforearm
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 14 Rhand
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 15 Larm
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 16 Lelbow
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 17 Lforearm
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 18 Lhand
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 19 FaceLB
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 20 FaceRB
        {  0.3f,  0.15f,  0.15f,  0.15f}, // 21 FaceLT
        {  0.3f,  0.15f,  0.15f,  0.15f}, // 22 FaceRT
        { 0.15f,  0.15f,  0.15f,  0.15f}, // 23 Rchest
        { 0.15f,  0.15f,  0.15f,  0.15f} // 24 Lchest
      };

      /**
       * @brief This LUT contains the number of children for each parent
       **/
      static const unsigned int LUT_nr_children[] = {
        0,            // 0 Lfoot
        1,            // 1 Lleg
        1,            // 2 Lknee
        1,            // 3 Lthigh
        0,            // 4 Rfoot
        1,            // 5 Rleg
        1,            // 6 Rknee
        1,            // 7 Rthigh
        1,            // 8 Rhips
        1,            // 9 Lhips
        4,            // 10 Neck
        1,            // 11 Rarm
        1,            // 12 Relbow
        1,            // 13 Rforearm
        0,            // 14 Rhand
        1,            // 15 Larm
        1,            // 16 Lelbow
        1,            // 17 Lforearm
        0,            // 18 Lhand
        1,            // 19 FaceLB
        1,            // 20 FaceRB
        0,            // 21 FaceLT
        0,            // 22 FaceRT
        2,            // 23 Rchest
        2             // 24 Lchest
      };

      } // End namespace label_skeletons
    } // End namespace people
  } // End namespace gpu
} // End namespace pcl
#endif