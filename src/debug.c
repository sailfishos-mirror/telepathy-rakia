/*
 * debug.h - Debug helpers for Telepathy-SofiaSIP, implementation
 * Copyright (C) 2007-2008 Nokia Corporation
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

#include "config.h"

#ifdef ENABLE_DEBUG

#include <stdarg.h>

#include <glib.h>

#include <telepathy-glib/debug.h>
#include <telepathy-glib/debug-sender.h>

#include "debug.h"

static TpsipDebugFlags tpsip_debug_flags = 0;

static const GDebugKey tpsip_debug_keys[] = {
  { "media-channel", TPSIP_DEBUG_MEDIA },
  { "connection",    TPSIP_DEBUG_CONNECTION },
  { "im",            TPSIP_DEBUG_IM },
  { "events",        TPSIP_DEBUG_EVENTS },
  { "sofia",         TPSIP_DEBUG_SOFIA },
};

void tpsip_debug_set_flags_from_env ()
{
  const gchar *flags_string;

  flags_string = g_getenv ("TPSIP_DEBUG");
  if (flags_string == NULL)
    flags_string = g_getenv ("SOFIASIP_DEBUG");

  if (flags_string != NULL)
    {
      tp_debug_set_flags (flags_string);

      tpsip_debug_set_flags (g_parse_debug_string (flags_string,
                                                   tpsip_debug_keys,
                                                   G_N_ELEMENTS(tpsip_debug_keys)));
    }
}

void tpsip_debug_set_flags (TpsipDebugFlags new_flags)
{
  tpsip_debug_flags |= new_flags;
}

gboolean tpsip_debug_flag_is_set (TpsipDebugFlags flag)
{
  return (flag & tpsip_debug_flags) ? TRUE : FALSE;
}

static GHashTable *flag_to_domains = NULL;

static const gchar *
debug_flag_to_domain (TpsipDebugFlags flag)
{
  if (G_UNLIKELY (flag_to_domains == NULL))
    {
      guint i;

      flag_to_domains = g_hash_table_new_full (g_direct_hash, g_direct_equal,
          NULL, g_free);

      for (i = 0; tpsip_debug_keys[i].value; i++)
        {
          GDebugKey key = (GDebugKey) tpsip_debug_keys[i];
          gchar *val;

          val = g_strdup_printf ("%s/%s", G_LOG_DOMAIN, key.key);
          g_hash_table_insert (flag_to_domains,
              GUINT_TO_POINTER (key.value), val);
        }
    }

  return g_hash_table_lookup (flag_to_domains, GUINT_TO_POINTER (flag));
}

void
tpsip_debug_free (void)
{
  if (flag_to_domains == NULL)
    return;

  g_hash_table_destroy (flag_to_domains);
  flag_to_domains = NULL;
}

static void
log_to_debug_sender (TpsipDebugFlags flag,
                     GLogLevelFlags level,
                     const gchar *message)
{
  TpDebugSender *dbg;
  GTimeVal now;

  dbg = tp_debug_sender_dup ();

  g_get_current_time (&now);

  tp_debug_sender_add_message (dbg, &now, debug_flag_to_domain (flag),
      level, message);

  g_object_unref (dbg);
}

void tpsip_log (TpsipDebugFlags flag,
                GLogLevelFlags level,
                const gchar *format,
                ...)
{
  gchar *message;
  va_list args;

  va_start (args, format);
  message = g_strdup_vprintf (format, args);
  va_end (args);

  log_to_debug_sender (flag, level, message);

  if (flag & tpsip_debug_flags)
    g_log (G_LOG_DOMAIN, level, "%s", message);

  g_free (message);
}

#endif /* ENABLE_DEBUG */
