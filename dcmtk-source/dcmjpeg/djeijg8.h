/*
 *
 *  Copyright (C) 1997-2005, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmjpeg
 *
 *  Author:  Norbert Olges, Marco Eichelberg
 *
 *  Purpose: compression routines of the IJG JPEG library configured for 8 bits/sample. 
 *
 *  Last Update:      $Author: lpysher $
 *  Update Date:      $Date: 2006/03/01 20:15:44 $
 *  Source File:      $Source: /cvsroot/osirix/osirix/Binaries/dcmtk-source/dcmjpeg/djeijg8.h,v $
 *  CVS/RCS Revision: $Revision: 1.1 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#ifndef DJEIJG8_H
#define DJEIJG8_H

#include "osconfig.h"
#include "oflist.h"
#include "djencabs.h"

extern "C"
{
  struct jpeg_compress_struct;
}

class DJCodecParameter;

/** this class encapsulates the compression routines of the
 *  IJG JPEG library configured for 8 bits/sample. 
 */
class DJCompressIJG8Bit: public DJEncoder
{
public:

  /** constructor for lossy JPEG
   *  @param cp codec parameters
   *  @param mode mode of operation
   *  @param quality compression quality
   */
  DJCompressIJG8Bit(const DJCodecParameter& cp, EJ_Mode mode, Uint8 quality);

  /** constructor for lossless JPEG
   *  @param cp codec parameters
   *  @param prediction predictor
   *  @param ptrans point transform
   */
  DJCompressIJG8Bit(const DJCodecParameter& cp, EJ_Mode mode, int prediction, int ptrans);

  /// destructor
  virtual ~DJCompressIJG8Bit();

  /** single frame compression routine for 16-bit raw pixel data.
   *  May only be called if bytesPerSample() == 2.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint16 *image_buffer,
    Uint8 *&to,
    Uint32 &length,
	Uint8 pixelRepresentation,
	double minUsed, double maxUsed);

  /** single frame compression routine for 8-bit raw pixel data.
   *  May only be called if bytesPerSample() == 1.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint8 *image_buffer,
    Uint8 *&to,
    Uint32 &length,
	Uint8 pixelRepresentation,
	double minUsed, double maxUsed);

  /** returns the number of bytes per sample that will be expected when encoding.
   */
  virtual Uint16 bytesPerSample() const { return 1; }

  /** returns the number of bits per sample that will be expected when encoding.
   */
  virtual Uint16 bitsPerSample() const { return 8; }

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  void initDestination(jpeg_compress_struct *cinfo);

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  int emptyOutputBuffer(jpeg_compress_struct *cinfo);

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  void termDestination(jpeg_compress_struct *cinfo);
  	
  /** callback function used to report warning messages and the like.
   *  Should not be called by user code directly.
   *  @param arg opaque pointer to JPEG compress structure
   */
  virtual void outputMessage(void *arg) const;

private:

  /// private undefined copy constructor
  DJCompressIJG8Bit(const DJCompressIJG8Bit&);

  /// private undefined copy assignment operator
  DJCompressIJG8Bit& operator=(const DJCompressIJG8Bit&);

  /// cleans up pixelDataList, called from destructor and error handlers
  void cleanup();

  /// codec parameters
  const DJCodecParameter *cparam;
  
  /// for lossy compression, defines compression quality factor
  Uint8 quality;

  /// for lossless compression, defines selection value
  int psv;

  /// for lossless compression, defines point transform
  int pt;

  /// enum for mode of operation (baseline, sequential, progressive etc.)
  EJ_Mode modeofOperation;

  /// list of compressed pixel data blocks  
  OFList<unsigned char *> pixelDataList;

  /// filled number of bytes in last block in pixelDataList
  size_t bytesInLastBlock;

};

#endif

/*
 * CVS/RCS Log
 * $Log: djeijg8.h,v $
 * Revision 1.1  2006/03/01 20:15:44  lpysher
 * Added dcmtkt ocvs not in xcode  and fixed bug with multiple monitors
 *
 * Revision 1.3  2005/12/08 16:59:27  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2001/11/19 15:13:29  meichel
 * Introduced verbose mode in module dcmjpeg. If enabled, warning
 *   messages from the IJG library are printed on ofConsole, otherwise
 *   the library remains quiet.
 *
 * Revision 1.1  2001/11/13 15:56:24  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
