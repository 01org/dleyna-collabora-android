/*
 * Copyright (C) 2007 OpenedHand Ltd.
 *
 * Author: Jorn Baayen <jorn@openedhand.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <libgupnp/gupnp-control-point.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <signal.h>
#include <glib.h>

#ifdef __BIONIC__
#include <android/log.h>
#define LOG_TAG "gupnp-tests-proxy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

GMainLoop *main_loop;

static void
interrupt_signal_handler (int signum)
{
        g_main_loop_quit (main_loop);
}

static void
subscription_lost_cb (GUPnPServiceProxy *proxy,
                      const GError      *reason,
                      gpointer           user_data)
{
        g_print ("Lost subscription: %s\n", reason->message);
#ifdef __BIONIC__
        LOGI ("Lost subscription: %s\n", reason->message);
#endif
}

static void
notify_cb (GUPnPServiceProxy *proxy,
           const char        *variable,
           GValue            *value,
           gpointer           user_data)
{
        g_print ("Received a notification for variable '%s':\n", variable);
        g_print ("\tvalue:     %d\n", g_value_get_uint (value));
        g_print ("\tuser_data: %s\n", (const char *) user_data);
#ifdef __BIONIC__
        LOGI ("Received a notification for variable '%s':", variable);
        LOGI ("\tvalue:     %d", g_value_get_uint (value));
        LOGI ("\tuser_data: %s", (const char *) user_data);
#endif
}

static void
service_proxy_available_cb (GUPnPControlPoint *cp,
                            GUPnPServiceProxy *proxy)
{
        const char *location;
        char *result = NULL;
        guint count, total;
        GError *error = NULL;

        location = gupnp_service_info_get_location (GUPNP_SERVICE_INFO (proxy));

        g_print ("ContentDirectory available:\n");
        g_print ("\tlocation: %s\n", location);
#ifdef __BIONIC__
        LOGI ("ContentDirectory available:");
        LOGI ("\tlocation: %s", location);
#endif

        /* We want to be notified whenever SystemUpdateID (of type uint)
         * changes */
        gupnp_service_proxy_add_notify (proxy,
                                        "SystemUpdateID",
                                        G_TYPE_UINT,
                                        notify_cb,
                                        (gpointer) "Test");

        /* Subscribe */
        g_signal_connect (proxy,
                          "subscription-lost",
                          G_CALLBACK (subscription_lost_cb),
                          NULL);

        gupnp_service_proxy_set_subscribed (proxy, TRUE);

        /* And test action IO */
        gupnp_service_proxy_send_action (proxy,
                                         "Browse",
                                         &error,
                                         /* IN args */
                                         "ObjectID",
                                                G_TYPE_STRING,
                                                "0",
                                         "BrowseFlag",
                                                G_TYPE_STRING,
                                                "BrowseDirectChildren",
                                         "Filter",
                                                G_TYPE_STRING,
                                                "*",
                                         "StartingIndex",
                                                G_TYPE_UINT,
                                                0,
                                         "RequestedCount",
                                                G_TYPE_UINT,
                                                0,
                                         "SortCriteria",
                                                G_TYPE_STRING,
                                                "",
                                         NULL,
                                         /* OUT args */
                                         "Result",
                                                G_TYPE_STRING,
                                                &result,
                                         "NumberReturned",
                                                G_TYPE_UINT,
                                                &count,
                                         "TotalMatches",
                                                G_TYPE_UINT,
                                                &total,
                                         NULL);

        if (error) {
                g_printerr ("Error: %s\n", error->message);
#ifdef __BIONIC__
                LOGW ("Error: %s\n", error->message);
#endif
                g_error_free (error);

                return;
        }

        g_print ("Browse returned:\n");
        g_print ("\tResult:         %s\n", result);
        g_print ("\tNumberReturned: %u\n", count);
        g_print ("\tTotalMatches:   %u\n", total);
#ifdef __BIONIC__
        LOGI ("Browse returned:");
        LOGI ("\tResult:         %s", result);
        LOGI ("\tNumberReturned: %u", count);
        LOGI ("\tTotalMatches:   %u", total);
#endif

        g_free (result);
}

static void
service_proxy_unavailable_cb (GUPnPControlPoint *cp,
                              GUPnPServiceProxy *proxy)
{
        const char *location;

        location = gupnp_service_info_get_location (GUPNP_SERVICE_INFO (proxy));

        g_print ("ContentDirectory unavailable:\n");
        g_print ("\tlocation: %s\n", location);
#ifdef __BIONIC__
        LOGI ("ContentDirectory unavailable:");
        LOGI ("\tlocation: %s", location);
#endif
}

int
gupnp_proxy_test_main (int argc, char **argv)
{
        GError *error;
        GUPnPContext *context;
        GUPnPControlPoint *cp;
#ifndef G_OS_WIN32
        struct sigaction sig_action;
#endif /* G_OS_WIN32 */

#if !GLIB_CHECK_VERSION(2,35,0)
        g_type_init ();
#endif
        setlocale (LC_ALL, "");

        error = NULL;
        context = g_initable_new (GUPNP_TYPE_CONTEXT, NULL, &error, NULL);
        if (error) {
                g_printerr ("Error creating the GUPnP context: %s\n",
			    error->message);
#ifdef __BIONIC__
                LOGW ("Error creating the GUPnP context: %s", error->message);
#endif
                g_error_free (error);

                return EXIT_FAILURE;
        }

        /* We're interested in everything */
        cp = gupnp_control_point_new
                (context, "urn:schemas-upnp-org:service:ContentDirectory:1");

        g_signal_connect (cp,
                          "service-proxy-available",
                          G_CALLBACK (service_proxy_available_cb),
                          NULL);
        g_signal_connect (cp,
                          "service-proxy-unavailable",
                          G_CALLBACK (service_proxy_unavailable_cb),
                          NULL);

        gssdp_resource_browser_set_active (GSSDP_RESOURCE_BROWSER (cp), TRUE);

        main_loop = g_main_loop_new (NULL, FALSE);

        /* Hook the handler for SIGTERM */
#ifndef G_OS_WIN32
        memset (&sig_action, 0, sizeof (sig_action));
        sig_action.sa_handler = interrupt_signal_handler;
        sigaction (SIGINT, &sig_action, NULL);
#else
        signal(SIGINT,interrupt_signal_handler);
#endif /* G_OS_WIN32 */

        g_main_loop_run (main_loop);
        g_main_loop_unref (main_loop);

        g_object_unref (cp);
        g_object_unref (context);

        return EXIT_SUCCESS;
}
