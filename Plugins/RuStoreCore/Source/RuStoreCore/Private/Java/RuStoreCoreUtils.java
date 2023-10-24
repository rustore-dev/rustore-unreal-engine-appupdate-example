// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreCore;

import android.app.Activity;
import android.app.Application;
import android.content.ClipboardManager;
import android.content.ClipData;
import android.content.Context;
import android.support.annotation.Keep;
import android.widget.Toast;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

@Keep
public class RuStoreCoreUtils
{
	@Keep
	public static void showToast(final Activity activity, String message)
	{
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(activity, message, Toast.LENGTH_LONG).show();
			}
		});
	}

	@Keep
	public static String ConvertToISO8601(Date date)
	{
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ssXXX");
		formatter.setTimeZone(TimeZone.getTimeZone("UTC"));
		return formatter.format(date);
	}

	@Keep
	public static void CopyToClipboard(final Activity activity, String text)
	{
		ClipboardManager clipboard = (ClipboardManager)activity.getSystemService(Context.CLIPBOARD_SERVICE);
		ClipData clip = ClipData.newPlainText("Copied Text", text);
		clipboard.setPrimaryClip(clip);
	}

	@Keep
	public static String GetFromClipboard(final Activity activity)
	{
		ClipboardManager clipboard = (ClipboardManager)activity.getSystemService(Context.CLIPBOARD_SERVICE);
		ClipData clip = clipboard.getPrimaryClip();

        if (clip == null) return null;
		CharSequence text = clip.getItemAt(0).getText();
		if (text == null) return null;

		return text.toString();
	}

	@Keep
	public static String GetStringResources(final Application application, String name)
	{
		int id = application.getResources().getIdentifier(name, "string", application.getPackageName());

		return application.getString(id);
	}

	@Keep
	public static RuStoreImage DownloadImage(String imageUrl) throws IOException
	{
		RuStoreImage image = new RuStoreImage();

		try {
			InputStream inputStream = new URL(imageUrl).openStream();
			Bitmap bitmap = BitmapFactory.decodeStream(inputStream);
		
			image.width = bitmap.getWidth();
			image.height = bitmap.getHeight();

			int[] pixels = new int[image.width * image.height];
			bitmap.getPixels(pixels, 0, image.width, 0, 0, image.width, image.height);

			image.bgra = new byte[4 * image.width * image.height];
			for (int i = 0; i < pixels.length; i++) {
				image.bgra[i * 4] = (byte)(pixels[i] & 0xFF);
				image.bgra[i * 4 + 1] = (byte)((pixels[i] >> 8) & 0xFF);
				image.bgra[i * 4 + 2] = (byte)((pixels[i] >> 16) & 0xFF);
				image.bgra[i * 4 + 3] = (byte)((pixels[i] >> 24) & 0xFF);
			}

			image.isComplete = true;
		} catch (IOException e) {
			image.width = 0;
			image.height = 0;
			image.bgra = new byte[0];
			image.isComplete = false;
		}

        return image;
    }
}
