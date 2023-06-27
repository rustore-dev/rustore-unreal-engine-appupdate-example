package com.Plugins.RuStoreCore;

import android.app.Activity;
import android.support.annotation.Keep;
import android.widget.Toast;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

@Keep
public class RuStoreCoreUtils
{
	@Keep
	public static void showToast(final Activity activity, String message)
	{
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run()
			{
				Toast.makeText(activity, message, Toast.LENGTH_LONG).show();

				System.gc();
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
}
