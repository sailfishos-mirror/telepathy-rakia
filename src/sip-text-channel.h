/*
 * sip-text-channel.h - Header for TpsipTextChannel
 * Copyright (C) 2005 Collabora Ltd.
 * Copyright (C) 2005 Nokia Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __TPSIP_TEXT_CHANNEL_H__
#define __TPSIP_TEXT_CHANNEL_H__

#include <glib-object.h>

#include <telepathy-glib/handle.h>

#include "sip-sofia-decls.h"

typedef struct _TpsipHandleStorage TpsipHandleStorage;

G_BEGIN_DECLS

typedef struct _TpsipTextChannel TpsipTextChannel;
typedef struct _TpsipTextChannelClass TpsipTextChannelClass;

struct _TpsipTextChannelClass {
    GObjectClass parent_class;
};

struct _TpsipTextChannel {
    GObject parent;
};

GType tpsip_text_channel_get_type(void);

/* TYPE MACROS */
#define TPSIP_TYPE_TEXT_CHANNEL \
  (tpsip_text_channel_get_type())
#define TPSIP_TEXT_CHANNEL(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TPSIP_TYPE_TEXT_CHANNEL, TpsipTextChannel))
#define TPSIP_TEXT_CHANNEL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), TPSIP_TYPE_TEXT_CHANNEL, TpsipTextChannelClass))
#define TPSIP_IS_TEXT_CHANNEL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TPSIP_TYPE_TEXT_CHANNEL))
#define TPSIP_IS_TEXT_CHANNEL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), TPSIP_TYPE_TEXT_CHANNEL))
#define TPSIP_TEXT_CHANNEL_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), TPSIP_TYPE_TEXT_CHANNEL, TpsipTextChannelClass))


void tpsip_text_channel_close (TpsipTextChannel *self);

void tpsip_text_channel_emit_message_status(TpsipTextChannel *obj,
                                          nua_handle_t *nh,
                                          int status);

void tpsip_text_channel_receive (TpsipTextChannel *obj,
                               TpHandle        sender,
                               const char     *message);


G_END_DECLS

#endif /* #ifndef __TPSIP_TEXT_CHANNEL_H__*/
