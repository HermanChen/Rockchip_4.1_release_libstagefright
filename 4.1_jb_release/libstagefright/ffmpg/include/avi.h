/*
 * copyright (c) 2001 Fabrice Bellard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


#ifndef AVFORMAT_AVI_H
#define AVFORMAT_AVI_H
#define AVIF_HASINDEX           0x00000010        // Index at end of file?
#define AVIF_MUSTUSEINDEX       0x00000020
#define AVIF_ISINTERLEAVED      0x00000100
#define AVIF_TRUSTCKTYPE        0x00000800        // Use CKType to find key frames?
#define AVIF_WASCAPTUREFILE     0x00010000
#define AVIF_COPYRIGHTED        0x00020000
#define AVI_MAX_RIFF_SIZE       0x40000000LL
#define AVI_MASTER_INDEX_SIZE   256

#define  SEEK_EROR       -1
#define  SEEK_SUCCESS    0
#define  SEEK_FAIL    1


/* index flags */
#define AVIIF_INDEX             0x10
#include "avformat.h"
#include "dv.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    int64_t  riff_end;
    int64_t  movi_end;
    int64_t  fsize;
    int64_t movi_list;
    int64_t last_pkt_pos;
    int index_loaded;
    int is_odml;
    int non_interleaved;
    int stream_index;
    DVDemuxContext* dv_demux;
} AVIContext;

#define NULL_IF_CONFIG_SMALL(x) NULL
int avi_read_packet(AVFormatContext *s, AVPacket *pkt);
int avi_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags);
void registerfile();
int avi_read_init(AVFormatContext *s,const char *filename,void* pReader);
int avi_read_close(AVFormatContext *s);
int file_open(AVFormatContext *s,const char *filename,void* pReader);

#ifdef __cplusplus
}
#endif

#endif /* AVFORMAT_AVI_H */
