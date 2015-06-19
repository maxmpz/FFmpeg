/*
 * Copyright (c) 2001 Fabrice Bellard
 * Copyright (c) 2002-2004 Michael Niedermayer <michaelni@gmx.at>
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

#ifndef AVCODEC_OPTIONS_TABLE_H
#define AVCODEC_OPTIONS_TABLE_H

#include <float.h>
#include <limits.h>
#include <stdint.h>

#include "libavutil/opt.h"
#include "avcodec.h"
#include "version.h"

#define OFFSET(x) offsetof(AVCodecContext,x)
#define DEFAULT 0 //should be NAN but it does not work as it is not a constant in glibc as required by ANSI/ISO C
//these names are too long to be readable
#define V AV_OPT_FLAG_VIDEO_PARAM
#define A AV_OPT_FLAG_AUDIO_PARAM
#define S AV_OPT_FLAG_SUBTITLE_PARAM
#define E AV_OPT_FLAG_ENCODING_PARAM
#define D AV_OPT_FLAG_DECODING_PARAM

#define AV_CODEC_DEFAULT_BITRATE 200*1000
// Begin PAMP change: use NULL_IF_CONFIG_SMALL() for options help labels, video options removed for CONFIG_NO_VIDEO
#define N(s) NULL_IF_CONFIG_SMALL(s)

static const AVOption avcodec_options[] = {
{"b", N("set bitrate (in bits/s)"), OFFSET(bit_rate), AV_OPT_TYPE_INT, {.i64 = AV_CODEC_DEFAULT_BITRATE }, 0, INT_MAX, A|V|E},
{"ab", N("set bitrate (in bits/s)"), OFFSET(bit_rate), AV_OPT_TYPE_INT, {.i64 = 128*1000 }, 0, INT_MAX, A|E},
#if !PAMP_CONFIG_NO_VIDEO
{"bt", N("Set video bitrate tolerance (in bits/s). In 1-pass mode, bitrate tolerance specifies how far "
       "ratecontrol is willing to deviate from the target average bitrate value. This is not related "
       "to minimum/maximum bitrate. Lowering tolerance too much has an adverse effect on quality."),
       OFFSET(bit_rate_tolerance), AV_OPT_TYPE_INT, {.i64 = AV_CODEC_DEFAULT_BITRATE*20 }, 1, INT_MAX, V|E},
#endif
{"flags", NULL, OFFSET(flags), AV_OPT_TYPE_FLAGS, {.i64 = DEFAULT }, 0, UINT_MAX, V|A|S|E|D, "flags"},
{"unaligned", N("allow decoders to produce unaligned output"), 0, AV_OPT_TYPE_CONST, { .i64 = CODEC_FLAG_UNALIGNED }, INT_MIN, INT_MAX, V | D, "flags" },
#if !PAMP_CONFIG_NO_VIDEO
{"mv4", N("use four motion vectors per macroblock (MPEG-4)"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_4MV }, INT_MIN, INT_MAX, V|E, "flags"},
{"qpel", N("use 1/4-pel motion compensation"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_QPEL }, INT_MIN, INT_MAX, V|E, "flags"},
{"loop", N("use loop filter"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_LOOP_FILTER }, INT_MIN, INT_MAX, V|E, "flags"},
{"qscale", N("use fixed qscale"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_QSCALE }, INT_MIN, INT_MAX, 0, "flags"},
#if FF_API_GMC
{"gmc", N("use gmc"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_GMC }, INT_MIN, INT_MAX, V|E, "flags"},
#endif
#if FF_API_MV0
{"mv0", N("always try a mb with mv=<0,0>"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_MV0 }, INT_MIN, INT_MAX, V|E, "flags"},
#endif
#if FF_API_INPUT_PRESERVED
{"input_preserved", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_INPUT_PRESERVED }, INT_MIN, INT_MAX, 0, "flags"},
#endif
{"pass1", N("use internal 2-pass ratecontrol in first  pass mode"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_PASS1 }, INT_MIN, INT_MAX, 0, "flags"},
{"pass2", N("use internal 2-pass ratecontrol in second pass mode"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_PASS2 }, INT_MIN, INT_MAX, 0, "flags"},
{"gray", N("only decode/encode grayscale"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_GRAY }, INT_MIN, INT_MAX, V|E|D, "flags"},
#if FF_API_EMU_EDGE
{"emu_edge", N("do not draw edges"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_EMU_EDGE }, INT_MIN, INT_MAX, 0, "flags"},
#endif
{"psnr", N("error[?] variables will be set during encoding"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_PSNR }, INT_MIN, INT_MAX, V|E, "flags"},
{"truncated", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_TRUNCATED }, INT_MIN, INT_MAX, 0, "flags"},
#if FF_API_NORMALIZE_AQP
{"naq", N("normalize adaptive quantization"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_NORMALIZE_AQP }, INT_MIN, INT_MAX, V|E, "flags"},
#endif
{"ildct", N("use interlaced DCT"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_INTERLACED_DCT }, INT_MIN, INT_MAX, V|E, "flags"},
{"low_delay", N("force low delay"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_LOW_DELAY }, INT_MIN, INT_MAX, V|D|E, "flags"},
{"global_header", N("place global headers in extradata instead of every keyframe"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_GLOBAL_HEADER }, INT_MIN, INT_MAX, V|A|E, "flags"},
#endif
{"bitexact", N("use only bitexact functions (except (I)DCT)"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_BITEXACT }, INT_MIN, INT_MAX, A|V|S|D|E, "flags"},
#if !PAMP_CONFIG_NO_VIDEO
{"aic", N("H.263 advanced intra coding / MPEG-4 AC prediction"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_AC_PRED }, INT_MIN, INT_MAX, V|E, "flags"},
{"ilme", N("interlaced motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_INTERLACED_ME }, INT_MIN, INT_MAX, V|E, "flags"},
{"cgop", N("closed GOP"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_CLOSED_GOP }, INT_MIN, INT_MAX, V|E, "flags"},
{"output_corrupt", N("Output even potentially corrupted frames"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG_OUTPUT_CORRUPT }, INT_MIN, INT_MAX, V|D, "flags"},
{"fast", N("allow non-spec-compliant speedup tricks"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_FAST }, INT_MIN, INT_MAX, V|E, "flags2"},
{"noout", N("skip bitstream encoding"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_NO_OUTPUT }, INT_MIN, INT_MAX, V|E, "flags2"},
{"ignorecrop", N("ignore cropping information from sps"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_IGNORE_CROP }, INT_MIN, INT_MAX, V|D, "flags2"},
#endif
{"local_header", N("place global headers at every keyframe instead of in extradata"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_LOCAL_HEADER }, INT_MIN, INT_MAX, V|E, "flags2"},
#if !PAMP_CONFIG_NO_VIDEO
{"chunks", N("Frame data might be split into multiple chunks"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_CHUNKS }, INT_MIN, INT_MAX, V|D, "flags2"},
{"showall", N("Show all frames before the first keyframe"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_SHOW_ALL }, INT_MIN, INT_MAX, V|D, "flags2"},
{"export_mvs", N("export motion vectors through frame side data"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_EXPORT_MVS}, INT_MIN, INT_MAX, V|D, "flags2"},
#endif
{"skip_manual", N("do not skip samples and export skip information as frame side data"), 0, AV_OPT_TYPE_CONST, {.i64 = CODEC_FLAG2_SKIP_MANUAL}, INT_MIN, INT_MAX, V|D, "flags2"},
#if !PAMP_CONFIG_NO_VIDEO
{"me_method", N("set motion estimation method"), OFFSET(me_method), AV_OPT_TYPE_INT, {.i64 = ME_EPZS }, INT_MIN, INT_MAX, V|E, "me_method"},
{"zero", N("zero motion estimation (fastest)"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_ZERO }, INT_MIN, INT_MAX, V|E, "me_method" },
{"full", N("full motion estimation (slowest)"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_FULL }, INT_MIN, INT_MAX, V|E, "me_method" },
{"epzs", N("EPZS motion estimation (default)"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_EPZS }, INT_MIN, INT_MAX, V|E, "me_method" },
{"esa", N("esa motion estimation (alias for full)"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_FULL }, INT_MIN, INT_MAX, V|E, "me_method" },
{"tesa", N("tesa motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_TESA }, INT_MIN, INT_MAX, V|E, "me_method" },
{"dia", N("diamond motion estimation (alias for EPZS)"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_EPZS }, INT_MIN, INT_MAX, V|E, "me_method" },
{"log", N("log motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_LOG }, INT_MIN, INT_MAX, V|E, "me_method" },
{"phods", N("phods motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_PHODS }, INT_MIN, INT_MAX, V|E, "me_method" },
{"x1", N("X1 motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_X1 }, INT_MIN, INT_MAX, V|E, "me_method" },
{"hex", N("hex motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_HEX }, INT_MIN, INT_MAX, V|E, "me_method" },
{"umh", N("umh motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_UMH }, INT_MIN, INT_MAX, V|E, "me_method" },
{"iter", N("iter motion estimation"), 0, AV_OPT_TYPE_CONST, {.i64 = ME_ITER }, INT_MIN, INT_MAX, V|E, "me_method" },
#endif
{"time_base", NULL, OFFSET(time_base), AV_OPT_TYPE_RATIONAL, {.dbl = 0}, INT_MIN, INT_MAX},
#if !PAMP_CONFIG_NO_VIDEO
{"g", N("set the group of picture (GOP) size"), OFFSET(gop_size), AV_OPT_TYPE_INT, {.i64 = 12 }, INT_MIN, INT_MAX, V|E},
#endif
{"ar", N("set audio sampling rate (in Hz)"), OFFSET(sample_rate), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, A|D|E},
{"ac", N("set number of audio channels"), OFFSET(channels), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, A|D|E},
{"cutoff", N("N(set cutoff bandwidth"), OFFSET(cutoff), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, A|E},
{"frame_size", NULL, OFFSET(frame_size), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, A|E},
{"frame_number", NULL, OFFSET(frame_number), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"delay", NULL, OFFSET(delay), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#if !PAMP_CONFIG_NO_VIDEO
{"qcomp", N("video quantizer scale compression (VBR). Constant of ratecontrol equation. "
          "Recommended range for default rc_eq: 0.0-1.0"),
          OFFSET(qcompress), AV_OPT_TYPE_FLOAT, {.dbl = 0.5 }, -FLT_MAX, FLT_MAX, V|E},
{"qblur", N("video quantizer scale blur (VBR)"), OFFSET(qblur), AV_OPT_TYPE_FLOAT, {.dbl = 0.5 }, -1, FLT_MAX, V|E},
{"qmin", N("minimum video quantizer scale (VBR)"), OFFSET(qmin), AV_OPT_TYPE_INT, {.i64 = 2 }, -1, 69, V|E},
{"qmax", N("maximum video quantizer scale (VBR)"), OFFSET(qmax), AV_OPT_TYPE_INT, {.i64 = 31 }, -1, 1024, V|E},
{"qdiff", N("maximum difference between the quantizer scales (VBR)"), OFFSET(max_qdiff), AV_OPT_TYPE_INT, {.i64 = 3 }, INT_MIN, INT_MAX, V|E},
{"bf", N("set maximum number of B frames between non-B-frames"), OFFSET(max_b_frames), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, -1, INT_MAX, V|E},
{"b_qfactor", N("QP factor between P- and B-frames"), OFFSET(b_quant_factor), AV_OPT_TYPE_FLOAT, {.dbl = 1.25 }, -FLT_MAX, FLT_MAX, V|E},
{"rc_strategy", N("ratecontrol method"), OFFSET(rc_strategy), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"b_strategy", N("strategy to choose between I/P/B-frames"), OFFSET(b_frame_strategy), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, V|E},
{"ps", N("RTP payload size in bytes"), OFFSET(rtp_payload_size), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"mv_bits", NULL, OFFSET(mv_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"header_bits", NULL, OFFSET(header_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"i_tex_bits", NULL, OFFSET(i_tex_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"p_tex_bits", NULL, OFFSET(p_tex_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"i_count", NULL, OFFSET(i_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"p_count", NULL, OFFSET(p_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#endif
{"skip_count", NULL, OFFSET(skip_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"misc_bits", NULL, OFFSET(misc_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"frame_bits", NULL, OFFSET(frame_bits), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"codec_tag", NULL, OFFSET(codec_tag), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"bug", N("work around not autodetected encoder bugs"), OFFSET(workaround_bugs), AV_OPT_TYPE_FLAGS, {.i64 = FF_BUG_AUTODETECT }, INT_MIN, INT_MAX, V|D, "bug"},
{"autodetect", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_AUTODETECT }, INT_MIN, INT_MAX, V|D, "bug"},
#if !PAMP_CONFIG_NO_VIDEO
#if FF_API_OLD_MSMPEG4
{"old_msmpeg4", N("some old lavc-generated MSMPEG4v3 files (no autodetection)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_OLD_MSMPEG4 }, INT_MIN, INT_MAX, V|D, "bug"},
#endif
{"xvid_ilace", N("Xvid interlacing bug (autodetected if FOURCC == XVIX)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_XVID_ILACE }, INT_MIN, INT_MAX, V|D, "bug"},
{"ump4", N("(autodetected if FOURCC == UMP4)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_UMP4 }, INT_MIN, INT_MAX, V|D, "bug"},
{"no_padding", N("padding bug (autodetected)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_NO_PADDING }, INT_MIN, INT_MAX, V|D, "bug"},
{"amv", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_AMV }, INT_MIN, INT_MAX, V|D, "bug"},
#if FF_API_AC_VLC
{"ac_vlc", N("illegal VLC bug (autodetected per FOURCC)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_AC_VLC }, INT_MIN, INT_MAX, V|D, "bug"},
#endif
{"qpel_chroma", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_QPEL_CHROMA }, INT_MIN, INT_MAX, V|D, "bug"},
{"std_qpel",N( "old standard qpel (autodetected per FOURCC/version)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_STD_QPEL }, INT_MIN, INT_MAX, V|D, "bug"},
{"qpel_chroma2", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_QPEL_CHROMA2 }, INT_MIN, INT_MAX, V|D, "bug"},
{"direct_blocksize", N("direct-qpel-blocksize bug (autodetected per FOURCC/version)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_DIRECT_BLOCKSIZE }, INT_MIN, INT_MAX, V|D, "bug"},
{"edge", N("edge padding bug (autodetected per FOURCC/version)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_EDGE }, INT_MIN, INT_MAX, V|D, "bug"},
{"hpel_chroma", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_HPEL_CHROMA }, INT_MIN, INT_MAX, V|D, "bug"},
{"dc_clip", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_DC_CLIP }, INT_MIN, INT_MAX, V|D, "bug"},
{"ms", N("work around various bugs in Microsoft's broken decoders"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_MS }, INT_MIN, INT_MAX, V|D, "bug"},
{"trunc", N("truncated frames"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_BUG_TRUNCATED}, INT_MIN, INT_MAX, V|D, "bug"},
#endif
{"strict", N("how strictly to follow the standards"), OFFSET(strict_std_compliance), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, A|V|D|E, "strict"},
{"very", N("strictly conform to a older more strict version of the spec or reference software"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_COMPLIANCE_VERY_STRICT }, INT_MIN, INT_MAX, V|D|E, "strict"},
{"strict", N("strictly conform to all the things in the spec no matter what the consequences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_COMPLIANCE_STRICT }, INT_MIN, INT_MAX, V|D|E, "strict"},
{"normal", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_COMPLIANCE_NORMAL }, INT_MIN, INT_MAX, V|D|E, "strict"},
{"unofficial", N("allow unofficial extensions"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_COMPLIANCE_UNOFFICIAL }, INT_MIN, INT_MAX, V|D|E, "strict"},
{"experimental", N("allow non-standardized experimental things"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_COMPLIANCE_EXPERIMENTAL }, INT_MIN, INT_MAX, V|D|E, "strict"},
#if !PAMP_CONFIG_NO_VIDEO
{"b_qoffset", N("QP offset between P- and B-frames"), OFFSET(b_quant_offset), AV_OPT_TYPE_FLOAT, {.dbl = 1.25 }, -FLT_MAX, FLT_MAX, V|E},
{"err_detect", N("set error detection flags"), OFFSET(err_recognition), AV_OPT_TYPE_FLAGS, {.i64 = 0 }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"crccheck", N("verify embedded CRCs"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_CRCCHECK }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"bitstream", N("detect bitstream specification deviations"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_BITSTREAM }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"buffer", N("detect improper bitstream length"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_BUFFER }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
#endif
{"explode", N("abort decoding on minor error detection"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_EXPLODE }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"ignore_err", N("ignore errors"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_IGNORE_ERR }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"careful",    N("consider things that violate the spec, are fast to check and have not been seen in the wild as errors"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_CAREFUL }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"compliant",  N("consider all spec non compliancies as errors"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_COMPLIANT }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
{"aggressive", N("consider things that a sane encoder should not do as an error"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_EF_AGGRESSIVE }, INT_MIN, INT_MAX, A|V|D, "err_detect"},
#if !PAMP_CONFIG_NO_VIDEO
{"has_b_frames", NULL, OFFSET(has_b_frames), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#endif
{"block_align", NULL, OFFSET(block_align), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#if !PAMP_CONFIG_NO_VIDEO
{"mpeg_quant", N("use MPEG quantizers instead of H.263"), OFFSET(mpeg_quant), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
#if FF_API_MPV_OPT
{"qsquish", N("deprecated, use encoder private options instead"), OFFSET(rc_qsquish), AV_OPT_TYPE_FLOAT, {.dbl = DEFAULT }, 0, 99, V|E},
{"rc_qmod_amp",  N("deprecated, use encoder private options instead"), OFFSET(rc_qmod_amp), AV_OPT_TYPE_FLOAT, {.dbl = DEFAULT }, -FLT_MAX, FLT_MAX, V|E},
{"rc_qmod_freq", N("deprecated, use encoder private options instead"), OFFSET(rc_qmod_freq), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
#endif
{"rc_override_count", NULL, OFFSET(rc_override_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#if FF_API_MPV_OPT
{"rc_eq", N("deprecated, use encoder private options instead"), OFFSET(rc_eq), AV_OPT_TYPE_STRING, {.str = NULL}, CHAR_MIN, CHAR_MAX, V|E},
#endif
{"maxrate", N("maximum bitrate (in bits/s). Used for VBV together with bufsize."), OFFSET(rc_max_rate), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, V|A|E},
{"minrate", N("minimum bitrate (in bits/s). Most useful in setting up a CBR encode. It is of little use otherwise."),
            OFFSET(rc_min_rate), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|A|E},
{"bufsize", N("set ratecontrol buffer size (in bits)"), OFFSET(rc_buffer_size), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, A|V|E},
#if FF_API_MPV_OPT
{"rc_buf_aggressivity", N("deprecated, use encoder private options instead"), OFFSET(rc_buffer_aggressivity), AV_OPT_TYPE_FLOAT, {.dbl = 1.0 }, -FLT_MAX, FLT_MAX, V|E},
#endif
{"i_qfactor", N("QP factor between P- and I-frames"), OFFSET(i_quant_factor), AV_OPT_TYPE_FLOAT, {.dbl = -0.8 }, -FLT_MAX, FLT_MAX, V|E},
{"i_qoffset", N("QP offset between P- and I-frames"), OFFSET(i_quant_offset), AV_OPT_TYPE_FLOAT, {.dbl = 0.0 }, -FLT_MAX, FLT_MAX, V|E},
#if FF_API_MPV_OPT
{"rc_init_cplx", N("deprecated, use encoder private options instead"), OFFSET(rc_initial_cplx), AV_OPT_TYPE_FLOAT, {.dbl = DEFAULT }, -FLT_MAX, FLT_MAX, V|E},
#endif
#endif
{"dct", N("DCT algorithm"), OFFSET(dct_algo), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, V|E, "dct"},
{"auto", N("autoselect a good one (default)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_AUTO }, INT_MIN, INT_MAX, V|E, "dct"},
{"fastint", N("fast integer"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_FASTINT }, INT_MIN, INT_MAX, V|E, "dct"},
#if FF_API_UNUSED_MEMBERS
{"int", N("accurate integer"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_INT }, INT_MIN, INT_MAX, V|E, "dct"},
#endif /* FF_API_UNUSED_MEMBERS */
{"mmx", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_MMX }, INT_MIN, INT_MAX, V|E, "dct"},
{"altivec", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_ALTIVEC }, INT_MIN, INT_MAX, V|E, "dct"},
{"faan", N("floating point AAN DCT"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DCT_FAAN }, INT_MIN, INT_MAX, V|E, "dct"},
#if !PAMP_CONFIG_NO_VIDEO
{"lumi_mask", N("compresses bright areas stronger than medium ones"), OFFSET(lumi_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, V|E},
{"tcplx_mask", N("temporal complexity masking"), OFFSET(temporal_cplx_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, V|E},
{"scplx_mask", N("spatial complexity masking"), OFFSET(spatial_cplx_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, V|E},
{"p_mask", N("inter masking"), OFFSET(p_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, V|E},
{"dark_mask", N("compresses dark areas stronger than medium ones"), OFFSET(dark_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, V|E},
{"idct", N("select IDCT implementation"), OFFSET(idct_algo), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, V|E|D, "idct"},
{"auto", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_AUTO }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"int", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_INT }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"simple", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLE }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"simplemmx", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEMMX }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"arm", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_ARM }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"altivec", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_ALTIVEC }, INT_MIN, INT_MAX, V|E|D, "idct"},
#if FF_API_ARCH_SH4
{"sh4", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SH4 }, INT_MIN, INT_MAX, V|E|D, "idct"},
#endif
{"simplearm", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEARM }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"simplearmv5te", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEARMV5TE }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"simplearmv6", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEARMV6 }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"simpleneon", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLENEON }, INT_MIN, INT_MAX, V|E|D, "idct"},
#if FF_API_ARCH_ALPHA
{"simplealpha", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEALPHA }, INT_MIN, INT_MAX, V|E|D, "idct"},
#endif
#if FF_API_UNUSED_MEMBERS
{"ipp", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_IPP }, INT_MIN, INT_MAX, V|E|D, "idct"},
#endif /* FF_API_UNUSED_MEMBERS */
{"xvid", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_XVID }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"xvidmmx", N("deprecated, for compatibility only"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_XVID }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"faani", N("floating point AAN IDCT"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_FAAN }, INT_MIN, INT_MAX, V|D|E, "idct"},
{"simpleauto", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_IDCT_SIMPLEAUTO }, INT_MIN, INT_MAX, V|E|D, "idct"},
{"slice_count", NULL, OFFSET(slice_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"ec", N("set error concealment strategy"), OFFSET(error_concealment), AV_OPT_TYPE_FLAGS, {.i64 = 3 }, INT_MIN, INT_MAX, V|D, "ec"},
{"guess_mvs", N("iterative motion vector (MV) search (slow)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_EC_GUESS_MVS }, INT_MIN, INT_MAX, V|D, "ec"},
{"deblock", N("use strong deblock filter for damaged MBs"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_EC_DEBLOCK }, INT_MIN, INT_MAX, V|D, "ec"},
{"favor_inter", N("favor predicting from the previous frame"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_EC_FAVOR_INTER }, INT_MIN, INT_MAX, V|D, "ec"},
{"bits_per_coded_sample", NULL, OFFSET(bits_per_coded_sample), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"pred", N("prediction method"), OFFSET(prediction_method), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "pred"},
{"left", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PRED_LEFT }, INT_MIN, INT_MAX, V|E, "pred"},
{"plane", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PRED_PLANE }, INT_MIN, INT_MAX, V|E, "pred"},
{"median", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PRED_MEDIAN }, INT_MIN, INT_MAX, V|E, "pred"},
{"aspect", N("sample aspect ratio"), OFFSET(sample_aspect_ratio), AV_OPT_TYPE_RATIONAL, {.dbl = 0}, 0, 10, V|E},
{"debug", N("print specific debug info"), OFFSET(debug), AV_OPT_TYPE_FLAGS, {.i64 = DEFAULT }, 0, INT_MAX, V|A|S|E|D, "debug"},
{"pict", N("picture info"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_PICT_INFO }, INT_MIN, INT_MAX, V|D, "debug"},
{"rc", N("rate control"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_RC }, INT_MIN, INT_MAX, V|E, "debug"},
{"bitstream", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_BITSTREAM }, INT_MIN, INT_MAX, V|D, "debug"},
{"mb_type", N("macroblock (MB) type"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_MB_TYPE }, INT_MIN, INT_MAX, V|D, "debug"},
{"qp", N("per-block quantization parameter (QP)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_QP }, INT_MIN, INT_MAX, V|D, "debug"},
#if FF_API_DEBUG_MV
{"mv", N("motion vector"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_MV }, INT_MIN, INT_MAX, V|D, "debug"},
#endif
{"dct_coeff", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_DCT_COEFF }, INT_MIN, INT_MAX, V|D, "debug"},
{"skip", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_SKIP }, INT_MIN, INT_MAX, V|D, "debug"},
{"startcode", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_STARTCODE }, INT_MIN, INT_MAX, V|D, "debug"},
#if FF_API_UNUSED_MEMBERS
{"pts", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_PTS }, INT_MIN, INT_MAX, V|D, "debug"},
#endif /* FF_API_UNUSED_MEMBERS */
{"er", N("error recognition"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_ER }, INT_MIN, INT_MAX, V|D, "debug"},
{"mmco", N("memory management control operations (H.264)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_MMCO }, INT_MIN, INT_MAX, V|D, "debug"},
{"bugs", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_BUGS }, INT_MIN, INT_MAX, V|D, "debug"},
{"vis_qp", N("visualize quantization parameter (QP), lower QP are tinted greener"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_VIS_QP }, INT_MIN, INT_MAX, V|D, "debug"},
{"vis_mb_type", N("visualize block types"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_VIS_MB_TYPE }, INT_MIN, INT_MAX, V|D, "debug"},
{"buffers", N("picture buffer allocations"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_BUFFERS }, INT_MIN, INT_MAX, V|D, "debug"},
{"thread_ops", N("threading operations"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_THREADS }, INT_MIN, INT_MAX, V|A|D, "debug"},
{"nomc", N("skip motion compensation"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_NOMC }, INT_MIN, INT_MAX, V|A|D, "debug"},
#if FF_API_VISMV
{"vismv", N("visualize motion vectors (MVs) (deprecated)"), OFFSET(debug_mv), AV_OPT_TYPE_FLAGS, {.i64 = DEFAULT }, 0, INT_MAX, V|D, "debug_mv"},
{"pf", N("forward predicted MVs of P-frames"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_VIS_MV_P_FOR }, INT_MIN, INT_MAX, V|D, "debug_mv"},
{"bf", N("forward predicted MVs of B-frames"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_VIS_MV_B_FOR }, INT_MIN, INT_MAX, V|D, "debug_mv"},
{"bb", N("backward predicted MVs of B-frames"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_DEBUG_VIS_MV_B_BACK }, INT_MIN, INT_MAX, V|D, "debug_mv"},
#endif
{"cmp", N("full-pel ME compare function"), OFFSET(me_cmp), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"subcmp", N("sub-pel ME compare function"), OFFSET(me_sub_cmp), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"mbcmp", N("macroblock compare function"), OFFSET(mb_cmp), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"ildctcmp", N("interlaced DCT compare function"), OFFSET(ildct_cmp), AV_OPT_TYPE_INT, {.i64 = FF_CMP_VSAD }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"dia_size", N("diamond type & size for motion estimation"), OFFSET(dia_size), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"last_pred", N("amount of motion predictors from the previous frame"), OFFSET(last_predictor_count), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"preme", N("pre motion estimation"), OFFSET(pre_me), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"precmp", N("pre motion estimation compare function"), OFFSET(me_pre_cmp), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"sad", N("sum of absolute differences, fast (default)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SAD }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"sse", N("sum of squared errors"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SSE }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"satd", N("sum of absolute Hadamard transformed differences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SATD }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"dct", N("sum of absolute DCT transformed differences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_DCT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"psnr", N("sum of squared quantization errors (avoid, low quality)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_PSNR }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"bit", N("number of bits needed for the block"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_BIT }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"rd", N("rate distortion optimal, slow"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_RD }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"zero", N("0"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_ZERO }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"vsad", N("sum of absolute vertical differences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_VSAD }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"vsse", N("sum of squared vertical differences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_VSSE }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"nsse", N("noise preserving sum of squared differences"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_NSSE }, INT_MIN, INT_MAX, V|E, "cmp_func"},
#if CONFIG_SNOW_ENCODER
{"w53", N("5/3 wavelet, only used in snow"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_W53 }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"w97", N("9/7 wavelet, only used in snow"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_W97 }, INT_MIN, INT_MAX, V|E, "cmp_func"},
#endif
{"dctmax", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_DCTMAX }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"chroma", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_CHROMA }, INT_MIN, INT_MAX, V|E, "cmp_func"},
{"pre_dia_size", N("diamond type & size for motion estimation pre-pass"), OFFSET(pre_dia_size), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"subq", N("sub-pel motion estimation quality"), OFFSET(me_subpel_quality), AV_OPT_TYPE_INT, {.i64 = 8 }, INT_MIN, INT_MAX, V|E},
{"dtg_active_format", NULL, OFFSET(dtg_active_format), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"me_range", N("limit motion vectors range (1023 for DivX player)"), OFFSET(me_range), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"ibias", N("intra quant bias"), OFFSET(intra_quant_bias), AV_OPT_TYPE_INT, {.i64 = FF_DEFAULT_QUANT_BIAS }, INT_MIN, INT_MAX, V|E},
{"pbias", N("inter quant bias"), OFFSET(inter_quant_bias), AV_OPT_TYPE_INT, {.i64 = FF_DEFAULT_QUANT_BIAS }, INT_MIN, INT_MAX, V|E},
{"global_quality", NULL, OFFSET(global_quality), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|A|E},
{"coder", NULL, OFFSET(coder_type), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E, "coder"},
{"vlc", N("variable length coder / Huffman coder"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CODER_TYPE_VLC }, INT_MIN, INT_MAX, V|E, "coder"},
{"ac", N("arithmetic coder"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CODER_TYPE_AC }, INT_MIN, INT_MAX, V|E, "coder"},
{"raw", N("raw (no encoding)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CODER_TYPE_RAW }, INT_MIN, INT_MAX, V|E, "coder"},
{"rle", N("run-length coder"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CODER_TYPE_RLE }, INT_MIN, INT_MAX, V|E, "coder"},
#if FF_API_UNUSED_MEMBERS
{"deflate", N("deflate-based coder"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_CODER_TYPE_DEFLATE }, INT_MIN, INT_MAX, V|E, "coder"},
#endif /* FF_API_UNUSED_MEMBERS */
{"context", N("context model"), OFFSET(context_model), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"slice_flags", NULL, OFFSET(slice_flags), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#if FF_API_XVMC
{"xvmc_acceleration", NULL, OFFSET(xvmc_acceleration), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#endif /* FF_API_XVMC */
{"mbd", N("macroblock decision algorithm (high quality mode)"), OFFSET(mb_decision), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, 2, V|E, "mbd"},
{"simple", N("use mbcmp (default)"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_MB_DECISION_SIMPLE }, INT_MIN, INT_MAX, V|E, "mbd"},
{"bits", N("use fewest bits"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_MB_DECISION_BITS }, INT_MIN, INT_MAX, V|E, "mbd"},
{"rd", N("use best rate distortion"), 0, AV_OPT_TYPE_CONST, {.i64 = FF_MB_DECISION_RD }, INT_MIN, INT_MAX, V|E, "mbd"},
#if FF_API_STREAM_CODEC_TAG
{"stream_codec_tag", NULL, OFFSET(stream_codec_tag), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
#endif
{"sc_threshold", N("scene change threshold"), OFFSET(scenechange_threshold), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
#if FF_API_MPV_OPT
{"lmin", N("deprecated, use encoder private options instead"), OFFSET(lmin), AV_OPT_TYPE_INT, {.i64 =  0 }, 0, INT_MAX, V|E},
{"lmax", N("deprecated, use encoder private options instead"), OFFSET(lmax), AV_OPT_TYPE_INT, {.i64 =  0 }, 0, INT_MAX, V|E},
#endif
{"nr", N("noise reduction"), OFFSET(noise_reduction), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"rc_init_occupancy", N("number of bits which should be loaded into the rc buffer before decoding starts"), OFFSET(rc_initial_buffer_occupancy), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"flags2", NULL, OFFSET(flags2), AV_OPT_TYPE_FLAGS, {.i64 = DEFAULT}, 0, UINT_MAX, V|A|E|D, "flags2"},
#if FF_API_ERROR_RATE
{"error", NULL, OFFSET(error_rate), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
#endif
#endif //!PAMP_CONFIG_NO_VIDEO
{"threads", NULL, OFFSET(thread_count), AV_OPT_TYPE_INT, {.i64 = 1 }, 0, INT_MAX, V|A|E|D, "threads"},
{"auto", N("autodetect a suitable number of threads to use"), 0, AV_OPT_TYPE_CONST, {.i64 = 0 }, INT_MIN, INT_MAX, V|E|D, "threads"},
#if !PAMP_CONFIG_NO_VIDEO
#if FF_API_MPV_OPT
{"me_threshold", N("motion estimation threshold"), OFFSET(me_threshold), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"mb_threshold", N("macroblock threshold"), OFFSET(mb_threshold), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
#endif
{"dc", N("intra_dc_precision"), OFFSET(intra_dc_precision), AV_OPT_TYPE_INT, {.i64 = 0 }, -8, 16, V|E},
{"nssew", N("nsse weight"), OFFSET(nsse_weight), AV_OPT_TYPE_INT, {.i64 = 8 }, INT_MIN, INT_MAX, V|E},
{"skip_top", N("number of macroblock rows at the top which are skipped"), OFFSET(skip_top), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|D},
{"skip_bottom", N("number of macroblock rows at the bottom which are skipped"), OFFSET(skip_bottom), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|D},
{"profile", NULL, OFFSET(profile), AV_OPT_TYPE_INT, {.i64 = FF_PROFILE_UNKNOWN }, INT_MIN, INT_MAX, V|A|E, "profile"},
{"unknown", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_UNKNOWN }, INT_MIN, INT_MAX, V|A|E, "profile"},
{"aac_main", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_MAIN }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_low", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_LOW }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_ssr", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_SSR }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_ltp", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_LTP }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_he", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_HE }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_he_v2", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_HE_V2 }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_ld", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_LD }, INT_MIN, INT_MAX, A|E, "profile"},
{"aac_eld", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_AAC_ELD }, INT_MIN, INT_MAX, A|E, "profile"},
{"mpeg2_aac_low", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG2_AAC_LOW }, INT_MIN, INT_MAX, A|E, "profile"},
{"mpeg2_aac_he", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG2_AAC_HE }, INT_MIN, INT_MAX, A|E, "profile"},
{"dts", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_DTS }, INT_MIN, INT_MAX, A|E, "profile"},
{"dts_es", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_DTS_ES }, INT_MIN, INT_MAX, A|E, "profile"},
{"dts_96_24", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_DTS_96_24 }, INT_MIN, INT_MAX, A|E, "profile"},
{"dts_hd_hra", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_DTS_HD_HRA }, INT_MIN, INT_MAX, A|E, "profile"},
{"dts_hd_ma", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_DTS_HD_MA }, INT_MIN, INT_MAX, A|E, "profile"},
{"mpeg4_sp",   NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG4_SIMPLE }, INT_MIN, INT_MAX, V|E, "profile"},
{"mpeg4_core", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG4_CORE }, INT_MIN, INT_MAX, V|E, "profile"},
{"mpeg4_main", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG4_MAIN }, INT_MIN, INT_MAX, V|E, "profile"},
{"mpeg4_asp",  NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_PROFILE_MPEG4_ADVANCED_SIMPLE }, INT_MIN, INT_MAX, V|E, "profile"},
{"level", NULL, OFFSET(level), AV_OPT_TYPE_INT, {.i64 = FF_LEVEL_UNKNOWN }, INT_MIN, INT_MAX, V|A|E, "level"},
{"unknown", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_LEVEL_UNKNOWN }, INT_MIN, INT_MAX, V|A|E, "level"},
{"lowres", N("decode at 1= 1/2, 2=1/4, 3=1/8 resolutions"), OFFSET(lowres), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, INT_MAX, V|A|D},
{"skip_threshold", N("frame skip threshold"), OFFSET(frame_skip_threshold), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"skip_factor", N("frame skip factor"), OFFSET(frame_skip_factor), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"skip_exp", N("frame skip exponent"), OFFSET(frame_skip_exp), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"skipcmp", N("frame skip compare function"), OFFSET(frame_skip_cmp), AV_OPT_TYPE_INT, {.i64 = FF_CMP_DCTMAX }, INT_MIN, INT_MAX, V|E, "cmp_func"},
#if FF_API_MPV_OPT
{"border_mask", N("deprecated, use encoder private options instead"), OFFSET(border_masking), AV_OPT_TYPE_FLOAT, {.dbl = DEFAULT }, -FLT_MAX, FLT_MAX, V|E},
#endif
{"mblmin", N("minimum macroblock Lagrange factor (VBR)"), OFFSET(mb_lmin), AV_OPT_TYPE_INT, {.i64 = FF_QP2LAMBDA * 2 }, 1, FF_LAMBDA_MAX, V|E},
{"mblmax", N("maximum macroblock Lagrange factor (VBR)"), OFFSET(mb_lmax), AV_OPT_TYPE_INT, {.i64 = FF_QP2LAMBDA * 31 }, 1, FF_LAMBDA_MAX, V|E},
{"mepc", N("motion estimation bitrate penalty compensation (1.0 = 256)"), OFFSET(me_penalty_compensation), AV_OPT_TYPE_INT, {.i64 = 256 }, INT_MIN, INT_MAX, V|E},
{"skip_loop_filter", N("skip loop filtering process for the selected frames"), OFFSET(skip_loop_filter), AV_OPT_TYPE_INT, {.i64 = AVDISCARD_DEFAULT }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"skip_idct"       , N("skip IDCT/dequantization for the selected frames"),    OFFSET(skip_idct),        AV_OPT_TYPE_INT, {.i64 = AVDISCARD_DEFAULT }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"skip_frame"      , N("skip decoding for the selected frames"),               OFFSET(skip_frame),       AV_OPT_TYPE_INT, {.i64 = AVDISCARD_DEFAULT }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"none"            , N("discard no frame"),                    0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_NONE    }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"default"         , N("discard useless frames"),              0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_DEFAULT }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"noref"           , N("discard all non-reference frames"),    0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_NONREF  }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"bidir"           , N("discard all bidirectional frames"),    0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_BIDIR   }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"nokey"           , N("discard all frames except keyframes"), 0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_NONKEY  }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"nointra"         , N("discard all frames except I frames"),  0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_NONINTRA}, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"all"             , N("discard all frames"),                  0, AV_OPT_TYPE_CONST, {.i64 = AVDISCARD_ALL     }, INT_MIN, INT_MAX, V|D, "avdiscard"},
{"bidir_refine", N("refine the two motion vectors used in bidirectional macroblocks"), OFFSET(bidir_refine), AV_OPT_TYPE_INT, {.i64 = 1 }, 0, 4, V|E},
{"brd_scale", N("downscale frames for dynamic B-frame decision"), OFFSET(brd_scale), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, 10, V|E},
{"keyint_min", N("minimum interval between IDR-frames"), OFFSET(keyint_min), AV_OPT_TYPE_INT, {.i64 = 25 }, INT_MIN, INT_MAX, V|E},
{"refs", N("reference frames to consider for motion compensation"), OFFSET(refs), AV_OPT_TYPE_INT, {.i64 = 1 }, INT_MIN, INT_MAX, V|E},
{"chromaoffset", N("chroma QP offset from luma"), OFFSET(chromaoffset), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|E},
{"trellis", N("rate-distortion optimal quantization"), OFFSET(trellis), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX, V|A|E},
#if FF_API_UNUSED_MEMBERS
{"sc_factor", N("multiplied by qscale for each frame and added to scene_change_score"), OFFSET(scenechange_factor), AV_OPT_TYPE_INT, {.i64 = 6 }, 0, INT_MAX, V|E},
#endif /* FF_API_UNUSED_MEMBERS */
{"mv0_threshold", NULL, OFFSET(mv0_threshold), AV_OPT_TYPE_INT, {.i64 = 256 }, 0, INT_MAX, V|E},
{"b_sensitivity", N("adjust sensitivity of b_frame_strategy 1"), OFFSET(b_sensitivity), AV_OPT_TYPE_INT, {.i64 = 40 }, 1, INT_MAX, V|E},
{"compression_level", NULL, OFFSET(compression_level), AV_OPT_TYPE_INT, {.i64 = FF_COMPRESSION_DEFAULT }, INT_MIN, INT_MAX, V|A|E},
{"min_prediction_order", NULL, OFFSET(min_prediction_order), AV_OPT_TYPE_INT, {.i64 = -1 }, INT_MIN, INT_MAX, A|E},
{"max_prediction_order", NULL, OFFSET(max_prediction_order), AV_OPT_TYPE_INT, {.i64 = -1 }, INT_MIN, INT_MAX, A|E},
{"timecode_frame_start", N("GOP timecode frame start number, in non-drop-frame format"), OFFSET(timecode_frame_start), AV_OPT_TYPE_INT64, {.i64 = -1 }, -1, INT64_MAX, V|E},
#endif
#if FF_API_REQUEST_CHANNELS
{"request_channels", N("set desired number of audio channels"), OFFSET(request_channels), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, 0, INT_MAX, A|D},
#endif
{"bits_per_raw_sample", NULL, OFFSET(bits_per_raw_sample), AV_OPT_TYPE_INT, {.i64 = DEFAULT }, INT_MIN, INT_MAX},
{"channel_layout", NULL, OFFSET(channel_layout), AV_OPT_TYPE_INT64, {.i64 = DEFAULT }, 0, INT64_MAX, A|E|D, "channel_layout"},
{"request_channel_layout", NULL, OFFSET(request_channel_layout), AV_OPT_TYPE_INT64, {.i64 = DEFAULT }, 0, INT64_MAX, A|D, "request_channel_layout"},
#if !PAMP_CONFIG_NO_VIDEO
{"rc_max_vbv_use", NULL, OFFSET(rc_max_available_vbv_use), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, 0.0, FLT_MAX, V|E},
{"rc_min_vbv_use", NULL, OFFSET(rc_min_vbv_overflow_use),  AV_OPT_TYPE_FLOAT, {.dbl = 3 },     0.0, FLT_MAX, V|E},
#endif
{"ticks_per_frame", NULL, OFFSET(ticks_per_frame), AV_OPT_TYPE_INT, {.i64 = 1 }, 1, INT_MAX, A|V|E|D},
#if !PAMP_CONFIG_NO_VIDEO
{"color_primaries", N("color primaries"), OFFSET(color_primaries), AV_OPT_TYPE_INT, {.i64 = AVCOL_PRI_UNSPECIFIED }, 1, AVCOL_PRI_NB-1, V|E|D, "color_primaries_type"},
{"bt709",       N("BT.709"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_BT709 },       INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"unspecified", N("Unspecified"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_UNSPECIFIED }, INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"bt470m",      N("BT.470 M"),    0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_BT470M },      INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"bt470bg",     N("BT.470 BG"),   0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_BT470BG },     INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"smpte170m",   N("SMPTE 170 M"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_SMPTE170M },   INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"smpte240m",   N("SMPTE 240 M"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_SMPTE240M },   INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"film",        N("Film"),        0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_FILM },        INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"bt2020",      N("BT.2020"),     0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_PRI_BT2020 },      INT_MIN, INT_MAX, V|E|D, "color_primaries_type"},
{"color_trc", N("color transfer characteristics"), OFFSET(color_trc), AV_OPT_TYPE_INT, {.i64 = AVCOL_TRC_UNSPECIFIED }, 1, AVCOL_TRC_NB-1, V|E|D, "color_trc_type"},
{"bt709",        N("BT.709"),           0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_BT709 },        INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"unspecified",  N("Unspecified"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_UNSPECIFIED },  INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"gamma22",      N("BT.470 M"),         0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_GAMMA22 },      INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"gamma28",      N("BT.470 BG"),        0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_GAMMA28 },      INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"smpte170m",    N("SMPTE 170 M"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_SMPTE170M },    INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"smpte240m",    N("SMPTE 240 M"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_SMPTE240M },    INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"linear",       N("Linear"),           0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_LINEAR },       INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"log",          N("Log"),              0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_LOG },          INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"log_sqrt",     N("Log square root"),  0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_LOG_SQRT },     INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"iec61966_2_4", N("IEC 61966-2-4"),    0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_IEC61966_2_4 }, INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"bt1361",       N("BT.1361"),          0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_BT1361_ECG },   INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"iec61966_2_1", N("IEC 61966-2-1"),    0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_IEC61966_2_1 }, INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"bt2020_10bit", N("BT.2020 - 10 bit"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_BT2020_10 },    INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"bt2020_12bit", N("BT.2020 - 12 bit"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_TRC_BT2020_12 },    INT_MIN, INT_MAX, V|E|D, "color_trc_type"},
{"colorspace", N("color space"), OFFSET(colorspace), AV_OPT_TYPE_INT, {.i64 = AVCOL_SPC_UNSPECIFIED }, 0, AVCOL_SPC_NB-1, V|E|D, "colorspace_type"},
{"rgb", N("RGB"),         0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_RGB },         INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"bt709", N("BT.709"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_BT709 },       INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"unspecified", N("Unspecified"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_UNSPECIFIED }, INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"fcc", N("FCC"),         0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_FCC },         INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"bt470bg", N("BT.470 BG"),   0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_BT470BG },     INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"smpte170m", N("SMPTE 170 M"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_SMPTE170M },   INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"smpte240m", N("SMPTE 240 M"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_SMPTE240M },   INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"ycocg", N("YCOCG"),       0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_YCOCG },       INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"bt2020_ncl", N("BT.2020 NCL"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_BT2020_NCL },  INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"bt2020_cl", N("BT.2020 CL"),  0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_SPC_BT2020_CL },   INT_MIN, INT_MAX, V|E|D, "colorspace_type"},
{"color_range", N("color range"), OFFSET(color_range), AV_OPT_TYPE_INT, {.i64 = AVCOL_RANGE_UNSPECIFIED }, 0, AVCOL_RANGE_NB-1, V|E|D, "color_range_type"},
{"unspecified", N("Unspecified"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_RANGE_UNSPECIFIED }, INT_MIN, INT_MAX, V|E|D, "color_range_type"},
{"mpeg", N("MPEG (219*2^(n-8))"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_RANGE_MPEG },        INT_MIN, INT_MAX, V|E|D, "color_range_type"},
{"jpeg", N("JPEG (2^n-1)"),       0, AV_OPT_TYPE_CONST, {.i64 = AVCOL_RANGE_JPEG },        INT_MIN, INT_MAX, V|E|D, "color_range_type"},
{"chroma_sample_location", N("chroma sample location"), OFFSET(chroma_sample_location), AV_OPT_TYPE_INT, {.i64 = AVCHROMA_LOC_UNSPECIFIED }, 0, AVCHROMA_LOC_NB-1, V|E|D, "chroma_sample_location_type"},
{"unspecified", N("Unspecified"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_UNSPECIFIED }, INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"left", N("Left"),        0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_LEFT },        INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"center", N("Center"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_CENTER },      INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"topleft", N("Top-left"),    0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_TOPLEFT },     INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"top", N("Top"),         0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_TOP },         INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"bottomleft", N("Bottom-left"), 0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_BOTTOMLEFT },  INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
{"bottom", N("Bottom"),      0, AV_OPT_TYPE_CONST, {.i64 = AVCHROMA_LOC_BOTTOM },      INT_MIN, INT_MAX, V|E|D, "chroma_sample_location_type"},
#endif
{"log_level_offset", N("set the log level offset"), OFFSET(log_level_offset), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX },
{"slices", N("number of slices, used in parallelized encoding"), OFFSET(slices), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, INT_MAX, V|E},
{"thread_type", N("select multithreading type"), OFFSET(thread_type), AV_OPT_TYPE_FLAGS, {.i64 = FF_THREAD_SLICE|FF_THREAD_FRAME }, 0, INT_MAX, V|A|E|D, "thread_type"},
{"slice", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_THREAD_SLICE }, INT_MIN, INT_MAX, V|E|D, "thread_type"},
{"frame", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_THREAD_FRAME }, INT_MIN, INT_MAX, V|E|D, "thread_type"},
{"audio_service_type", N("audio service type"), OFFSET(audio_service_type), AV_OPT_TYPE_INT, {.i64 = AV_AUDIO_SERVICE_TYPE_MAIN }, 0, AV_AUDIO_SERVICE_TYPE_NB-1, A|E, "audio_service_type"},
{"ma", N("Main Audio Service"), 0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_MAIN },              INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"ef", N("Effects"),            0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_EFFECTS },           INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"vi", N("Visually Impaired"),  0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED }, INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"hi", N("Hearing Impaired"),   0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED },  INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"di", N("Dialogue"),           0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_DIALOGUE },          INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"co", N("Commentary"),         0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_COMMENTARY },        INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"em", N("Emergency"),          0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_EMERGENCY },         INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"vo", N("Voice Over"),         0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_VOICE_OVER },        INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"ka", N("Karaoke"),            0, AV_OPT_TYPE_CONST, {.i64 = AV_AUDIO_SERVICE_TYPE_KARAOKE },           INT_MIN, INT_MAX, A|E, "audio_service_type"},
{"request_sample_fmt", N("sample format audio decoders should prefer"), OFFSET(request_sample_fmt), AV_OPT_TYPE_SAMPLE_FMT, {.i64=AV_SAMPLE_FMT_NONE}, -1, INT_MAX, A|D, "request_sample_fmt"},
{"pkt_timebase", NULL, OFFSET(pkt_timebase), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0, INT_MAX, 0},
#if !PAMP_CONFIG_NO_VIDEO
{"sub_charenc", N("set input text subtitles character encoding"), OFFSET(sub_charenc), AV_OPT_TYPE_STRING, {.str = NULL}, CHAR_MIN, CHAR_MAX, S|D},
{"sub_charenc_mode", N("set input text subtitles character encoding mode"), OFFSET(sub_charenc_mode), AV_OPT_TYPE_FLAGS, {.i64 = FF_SUB_CHARENC_MODE_AUTOMATIC}, -1, INT_MAX, S|D, "sub_charenc_mode"},
{"do_nothing",  NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_SUB_CHARENC_MODE_DO_NOTHING},  INT_MIN, INT_MAX, S|D, "sub_charenc_mode"},
{"auto",        NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_SUB_CHARENC_MODE_AUTOMATIC},   INT_MIN, INT_MAX, S|D, "sub_charenc_mode"},
{"pre_decoder", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_SUB_CHARENC_MODE_PRE_DECODER}, INT_MIN, INT_MAX, S|D, "sub_charenc_mode"},
{"refcounted_frames", NULL, OFFSET(refcounted_frames), AV_OPT_TYPE_INT, {.i64 = 0}, 0, 1, A|V|D },
{"side_data_only_packets", NULL, OFFSET(side_data_only_packets), AV_OPT_TYPE_INT, { .i64 = 0 }, 0, 1, A|V|E },
{"skip_alpha", N("Skip processing alpha"), OFFSET(skip_alpha), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, 1, V|D },
{"field_order", N("Field order"), OFFSET(field_order), AV_OPT_TYPE_INT, {.i64 = AV_FIELD_UNKNOWN }, 0, 5, V|D|E, "field_order" },
{"progressive", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = AV_FIELD_PROGRESSIVE }, 0, 0, V|D|E, "field_order" },
{"tt", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = AV_FIELD_TT }, 0, 0, V|D|E, "field_order" },
{"bb", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = AV_FIELD_BB }, 0, 0, V|D|E, "field_order" },
{"tb", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = AV_FIELD_TB }, 0, 0, V|D|E, "field_order" },
{"bt", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = AV_FIELD_BT }, 0, 0, V|D|E, "field_order" },
#endif
{"dump_separator", N("set information dump field separator"), OFFSET(dump_separator), AV_OPT_TYPE_STRING, {.str = NULL}, CHAR_MIN, CHAR_MAX, A|V|S|D|E},

{"codec_whitelist", N("List of decoders that are allowed to be used"), OFFSET(codec_whitelist), AV_OPT_TYPE_STRING, { .str = NULL },  CHAR_MIN, CHAR_MAX, A|V|S|D },
#if !PAMP_CONFIG_NO_VIDEO
{"pixel_format", N("set pixel format"), OFFSET(pix_fmt), AV_OPT_TYPE_PIXEL_FMT, {.i64=AV_PIX_FMT_NONE}, -1, INT_MAX, 0 },
{"video_size", N("set video size"), OFFSET(width), AV_OPT_TYPE_IMAGE_SIZE, {.str=NULL}, 0, INT_MAX, 0 },
#endif
{NULL},
};

#undef N
// End PAMP change

#undef A
#undef V
#undef S
#undef E
#undef D
#undef DEFAULT
#undef OFFSET

#endif /* AVCODEC_OPTIONS_TABLE_H */
