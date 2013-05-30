/*
 * dLeyna
 *
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Tom Keel <thomas.keel@intel.com>
 */

package com.intel.dleyna.dleynademo;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.intel.dleyna.RendererCallbackInterface;
import com.intel.dleyna.RendererInterface;

/**
 * This is the main Activity of the dLeyna demo app.
 * @author Tom Keel
 */
public class MainActivity extends Activity {

    private static final String TAG = App.TAG;

    private Prefs prefs = Prefs.getInstance();

    // Widgets.
    private TextView ttyTextView;
    private Button clearButton;

    /** The application package containing the Renderer service. */
    private static final String RENDERER_SERVICE_PACKAGE = "com.intel.dleyna.dleynademo";

    /** The class implementing the Renderer service. */
    private static final String RENDERER_SERVICE_CLASS = "com.intel.dleyna.RendererService";

    /** The Binder interface to the Renderer service. */
    private RendererInterface rendererService;

    private boolean rendererServiceBound;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (App.LOG) Log.i(TAG, "MainActivity: onCreate");
        setContentView(R.layout.main);
        ttyTextView = (TextView) findViewById(R.id.tty_text_view);
        ttyTextView.setMovementMethod(new ScrollingMovementMethod()); // makes it scrollable...
        clearButton = (Button) findViewById(R.id.clear_button);
        clearButton.setOnClickListener(clearButtonListener);
        showHelp();
    }

    protected void onStart() {
        super.onStart();
        if (App.LOG) Log.i(TAG, "MainActivity: onStart");
        Intent intent = new Intent();
        intent.setClassName(RENDERER_SERVICE_PACKAGE, RENDERER_SERVICE_CLASS);
        try {
            rendererServiceBound = bindService(intent, RendererConnection, Context.BIND_AUTO_CREATE);
        } catch (SecurityException e) {
        }
        if (!rendererServiceBound) {
            Log.w(TAG, "MainActivity: onStart: can't bind to renderer service");
            // For some crazy reason you have to have to unbind a service even if
            // the bind failed, or you'll get a "leaked ServiceConnection" warning.
            unbindService(RendererConnection);
        }
    }

    protected void onResume() {
        super.onResume();
        if (App.LOG) Log.i(TAG, "MainActivity: onResume");
        setEnabledStateOfWidgets(true);
    }

    protected void onPause() {
        super.onPause();
        if (App.LOG) Log.i(TAG, "MainActivity: onPause");
    }

    protected void onStop() {
        super.onStop();
        if (App.LOG) Log.i(TAG, "MainActivity: onStop");
    }

    protected void onDestroy() {
        super.onDestroy();
        if (rendererServiceBound) {
            unbindService(RendererConnection);
            rendererServiceBound = false;
        }
        if (App.LOG) Log.i(TAG, "MainActivity: onDestroy");
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_options, menu);
        menu.findItem(R.id.mi_settings).setIcon(android.R.drawable.ic_menu_preferences);
        return true;
    }

    public boolean onPrepareOptionsMenu(Menu menu) {
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case R.id.mi_settings:
            startActivity(new Intent(this, PrefsActivity.class));
            return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }

    private final OnClickListener clearButtonListener = new OnClickListener() {
        public void onClick(View v) {
            ttyTextView.setText(null);
        }
    };

    private final ServiceConnection RendererConnection = new ServiceConnection() {

        public void onServiceConnected(ComponentName className, IBinder b) {
            if (App.LOG) Log.i(TAG, "MainActivity: onServiceConnected");
            rendererService = RendererInterface.Stub.asInterface(b);
            try {
                rendererService.registerCallback(rendererCallback);
            } catch (RemoteException e) {
                 e.printStackTrace();
            }
        }

        public void onServiceDisconnected(ComponentName arg0) {
            if (App.LOG) Log.i(TAG, "MainActivity: onServiceDisconnected");
            rendererService = null;
        }
    };

    /**
     * Callbacks from the Renderer service via Binder are handled here.
     */
    private final RendererCallbackInterface rendererCallback =
            new RendererCallbackInterface.Stub() {
    };


    private void setEnabledStateOfWidgets(boolean enabled) {
        clearButton.setEnabled(enabled);
    }

    private void writeTty(CharSequence cs) {
        ttyTextView.append(cs);
        ttyTextView.bringPointIntoView(ttyTextView.length() - 1);
    }

    private static final String help =
        "This app will someday demonstrate dLeyna.\n" +
        "\n";

    private void showHelp() {
        ttyTextView.append(help);
    }
}
