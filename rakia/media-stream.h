/*
 * sip-media-stream.h - Header for RakiaMediaStream
 * Copyright (C) 2005 Collabora Ltd.
 * Copyright (C) 2005-2010 Nokia Corporation
 *
 * This work is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __RAKIA_MEDIA_STREAM_H__
#define __RAKIA_MEDIA_STREAM_H__

#include <glib-object.h>
#include <telepathy-glib/dbus-properties-mixin.h>
#include <telepathy-glib/enums.h>
#include <sofia-sip/sdp.h>

#include "rakia/sip-media.h"

G_BEGIN_DECLS

typedef struct _RakiaMediaStream RakiaMediaStream;
typedef struct _RakiaMediaStreamClass RakiaMediaStreamClass;
typedef struct _RakiaMediaStreamPrivate RakiaMediaStreamPrivate;

struct _RakiaMediaStreamClass {
    GObjectClass parent_class;
    TpDBusPropertiesMixinClass dbus_props_class;
};

struct _RakiaMediaStream {
    GObject parent;
    RakiaMediaStreamPrivate *priv;
};

GType rakia_media_stream_get_type(void);

/* TYPE MACROS */
#define RAKIA_TYPE_MEDIA_STREAM \
  (rakia_media_stream_get_type())
#define RAKIA_MEDIA_STREAM(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), RAKIA_TYPE_MEDIA_STREAM, RakiaMediaStream))
#define RAKIA_MEDIA_STREAM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), RAKIA_TYPE_MEDIA_STREAM, RakiaMediaStreamClass))
#define RAKIA_IS_MEDIA_STREAM(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), RAKIA_TYPE_MEDIA_STREAM))
#define RAKIA_IS_MEDIA_STREAM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), RAKIA_TYPE_MEDIA_STREAM))
#define RAKIA_MEDIA_STREAM_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), RAKIA_TYPE_MEDIA_STREAM, RakiaMediaStreamClass))

/***********************************************************************
 * Additional declarations (not based on generated templates)
 ***********************************************************************/

void rakia_media_stream_close (RakiaMediaStream *self);
guint rakia_media_stream_get_id (RakiaMediaStream *self);
guint rakia_media_stream_get_media_type (RakiaMediaStream *self);

void rakia_media_stream_set_playing (RakiaMediaStream *self, gboolean playing);
void rakia_media_stream_set_sending (RakiaMediaStream *self, gboolean sending);
void rakia_media_stream_set_direction (RakiaMediaStream *stream,
                                       TpMediaStreamDirection direction,
                                       guint pending_send_mask);
void rakia_media_stream_apply_pending_direction (RakiaMediaStream *stream,
                                                 guint pending_send_mask);
TpMediaStreamDirection rakia_media_stream_get_requested_direction (RakiaMediaStream *self);
gboolean rakia_media_stream_is_local_ready (RakiaMediaStream *self);
gboolean rakia_media_stream_is_codec_intersect_pending (RakiaMediaStream *self);
void rakia_media_stream_start_telephony_event (RakiaMediaStream *self, guchar event);
void rakia_media_stream_stop_telephony_event  (RakiaMediaStream *self);
gboolean rakia_media_stream_request_hold_state (RakiaMediaStream *self,
                                                gboolean hold);

guint rakia_tp_media_type (sdp_media_e sip_mtype);


RakiaSipMedia *rakia_media_stream_get_media (RakiaMediaStream *stream);

G_END_DECLS

#endif /* #ifndef __RAKIA_MEDIA_STREAM_H__*/
